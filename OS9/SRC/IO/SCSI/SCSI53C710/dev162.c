/*
 * support.c - NCR 53C710 SIOP and Motorola mVme162 specific subroutines.
 */
 
/*
 * Copyright 1991, 1994, 1995, 1996 by Microware Systems Corporation
 * Reproduced Under License
 *
 * This source code is the proprietary confidential property of
 * Microware Systems Corporation, and is provided to licensee
 * solely for documentation and educational purposes. Reproduction,
 * publication, or distribution in any form to any party other than
 * the licensee is strictly prohibited.
 */

/*
 * Adapted from dev167.c
 */
 
#include <scsisiop.h>
#include <ncrsiop.h>
#include <dev162.h>
#include <mcchip.h>

/*
 *	Function:
 *		get_siop_clock - return the value of SCLK to the calling process. 
 *
 *  Synopsis:
 *		int get_siop_clock( void )
 * 
 *  Description:
 *		This routine obtains the system BCLK (Bus Clock) from the MCChip
 *  and converts it to the SCLK (clock on NCR 53c710 chip) value.
 *  The return value is an integral value of SCLK in MHz.
 *
 *  Port Notes:
 *		This routine knows intimatly the method of providing SCLK to the
 *  SIOP.  SCLK is used to derive the SCSI core clock, which in tern
 *  then defines all SCSI bus cycles that the SIOP performs.  If it
 *  is possible an equivalent subroutine should be created and the flag
 *  -dSCLK added to the CFLAGS definition in the makefile.  If so desired,
 *  it is possible to define as a constant in "scsi710.h" in which case
 *  -dSCLK should not be present in the makefile.  If defining SCLK as
 *  a constant it should be an integral value in MHz.
 */

#if defined (__STDC__) || defined (_ANSI_EXT)
u_int8 get_siop_clock( void )
#else
u_int8 get_siop_clock()
#endif
{
	MCc162VR mcc = (MCc162VR) &(MCChip->M162VR);
	
	return( (u_int8) ((mcc->V0_33Mhz) ? (33*2) : (25*2)));
}


/*
 * Function: 
 *		chipreset - reset SIOP and reset parameters
 *
 * Synopsis:
 * 		error_code chipreset( Lstat lst )
 *
 * Description:
 *		This routine will perform a software reset of the SIOP and
 * reload the parameters needed for the chips proper function.
 *
 */
#if defined (__STDC__) || defined (_ANSI_EXT)
error_code chipreset( Lstat lst )
#else
error_code chipreset( lst )
Lstat lst;
#endif
{
	Siop_p const siop = (Siop_p)  lst->hdware; /* set hardware pointer */
	error_code error;
	
	if ( (error = ncr_reset( lst )) != SUCCESS)
		return error;
	
	/* set DMA parameters -  DMA burst = 8 */

	outc( &siop->dmode, (B_BL0 | B_BL1 | B_FC2) );

	/* cache line burst & snoop  */
	outc( &siop->ctest7, inc( &siop->ctest7 ) | B_TT1 | LSCX ); 

	return SUCCESS; 						/* all ok */
}

/*
 * check the address from the descriptor to see if the 710 chip is
 * really there or not.
 */
error_code hwprobe(u_int32 address)
{
    Siop_p const siop = (Siop_p) address; /* set hardware pointer */

    if (address != NCR710Base)
        return EOS_HARDWARE;

#ifdef NOACK
    outc( &siop->dcntl, 0);     /* Enable ACK: set up as slave device */
#else
    outc( &siop->dcntl, B_EA );     /* Enable ACK: set up as slave device */
#endif

    /* check DMA FIFO EMPTY FLAGS to see if hardware is working */
	
    if ( (inc(&siop->dstat) != 0x80) || (inc(&siop->ctest1) != 0xf0))
        return EOS_HARDWARE;		/* Not NCR 710 Device */

    return SUCCESS;
}

/*
 *	Function:
 *	 	start_siop - start up the NCR 53C710 SIOP for use. 
 *
 *  Synopsis:
 *		int start_siop( Lstat lst )
 *
 *  Description:
 *		Performs the 1 time initialization of the NCR 53c710 chip
 *  and the driver static storage.  The proceedure is:
 *
 *      - init the static storage
 *      - disable interrupts from SIOP via the MCchip
 *      - condition the SIOP.
 *      - enable SIOP interrupts
 *      - enable interrupts from the SIOP via the MCchip
 *      - start the SIOP script at the "wait" entry.
 *
 *  See Also:
 *		threadit()
 * 
 *  Caveats:
 *		This routine must set the clock divisor for the SIOP.  Without
 *  this being done properly the SIOP will not be able to properly 
 *  transact the SCSI protocol.
 *		The initial script that is defined as physical thread is the
 *  that of the SELFID.  While this thread is not used normally, it
 *  provides a means of catching problems (i.e. someone selects us
 *  which would be very bad, since we are not properly a target 
 *  device!)  It provides a set of scratch locations that can be
 *  used to sink data from the SIOP.
 *
 *  See Also:
 *		dma_dmabuserr(), irq()  [irq.c]
 *      stop_siop()
 *
 *  Port Notes:
 *		This routine knows the hardware intimatly.  It must condition
 *  the interrupts from the SIOP to the CPU.  In the case of the
 *  mVme162 this is done via an ASIC (MCC).  Action points:
 *    - evaluate the interrupts being enabled as a handler must be
 *      present for each.  The interrupts that are enabled also have
 *      implications for the SCSI SCRIPTS.
 *    - evaluate the DMA mode (we use cache line burst mode).  There
 *      are far reaching implications of how the DMA is throttled on
 *      the bus and in some respects governs the means of error recovery
 *      that is used.
 */
#if defined (__STDC__) || defined (_ANSI_EXT)
error_code start_siop( Lstat lst )
#else
error_code start_siop( lst )
Lstat lst;						/* static storage */
#endif
{
	MCc162VR mccvr = (MCc162VR) &(MCChip->M162VR);
	MCcICR mccsicr = (MCcICR) &(MCChip->SICR);
	int32 clk,temp;
	error_code error;
	Lthread lth;				/* logical thread pointer */

	/*  Verify the device presence */
	
	if (mccvr->V2_NOSCSI)		/* if SCSI is missing */

#if defined (__STDC__)
		return EOS_NOTRDY;
#else
		return E_NOTRDY;
#endif

	mccsicr->IEN =  FALSE;		/* disable interrupts from SIOP */

	if ( (error = chipreset( lst )) != SUCCESS)		/* reset the SIOP chip */
		return error;

	mccsicr->ILVL = lst->irqlevel;		/* set SIOP interrupt level */
	mccsicr->IEN =  TRUE;				/* enable interrupts from SIOP */

	coherent();	
	ncr_start( lst );					/* Start IDLE thread */
	return SUCCESS; 						/* all ok */

}	/* end Start_siop */

/*
 *	Function:
 *	 	stop_siop - stop up the NCR 53C710 SIOP.
 *
 *  Synopsis:
 *		int stop_siop( Lstat lst )
 *
 *  Description:
 *		This routine should terminate all activity on the SIOP and
 *  disable SIOP interrupts.
 *
 *  WARNING:  This routine should be called only from term() since
 *            what it is doing is fatal to the SIOP and the SCSI BUS
 *            if a command is being processed!
 * 
 *  See Also:
 *		start_siop()
 */

#if defined (__STDC__) || defined (_ANSI_EXT)
void stop_siop( Lstat lst )
#else
void stop_siop( lst )
Lstat lst;				/* static storage */
#endif
{
	MCcICR mccsicr = (MCcICR) &(MCChip->SICR);

	mccsicr->IEN =  FALSE;			/* disable interrupts from SIOP */
	
	ncr_stop( lst );				/* soft reset of siop */
}

/*
 *  Function:
 *		buscondition - decide if bus error conditon was "hard" or "soft".
 *
 *  Synopsis:
 *		int buscondition( void )
 *
 *  Returns:
 *		TRUE if error is fatal
 *      FALSE if error is non-fatal
 *
 *  Description:
 *		This is a very crucial routine for the proper operation of
 *  the SIOP.  If the SIOP encounters a bus error condition the cause
 *  of the bus error must be assesed and  continue/abort decision
 *  made.  If the bus error is a result of access timeout the bus error
 *  is considered soft and the operation can be restarted with a fair
 *  chance of successful completion.  If the error cannot be determined
 *  or is a result of non-existant address access, the error should be
 *  considered hard and aborted.
 *
 *  Port Notes:
 *		The mVme162 offers status of the bus latched into the MCchip
 *  for access to the local bus.  As a result a determination about local
 *  bus errors can be made.  The handling in the routine below reflects
 *  this capability.  The sad fact about the EXT bit is that it
 *  tells us that we have received an error from the VMEChip2 when
 *  trying to reach off-board.  We cannot be certain that the problem
 *  was associated with the NCR chip so we must treat these problems
 *  as hard errors even though the VMEChip2 may be reporting a VME bus
 *  access timeout.
 *		In porting to another board, care must be taken
 *  to properly reproduce the action of this  code or failing that,
 *  insure that no local bus timeouts are possible and no pointers
 *  to non-existant memory can be submitted to the SIOP.  
 */
#if defined (__STDC__) || defined (_ANSI_EXT)
error_code buscondition( void )
#else
error_code buscondition()
#endif
{
	MCcSESR mccsesr = (MCcSESR) &(MCChip->SESR);
	u_int mccstatus;

	mccstatus = !(mccsesr->LTO);		/* get error status register */
	mccsesr->SCLR = TRUE;				/* clear status */
	return( mccstatus );
}

/*
 *	Function:
 *		SCSI_reset - send a SCSI BUS RESET
 *
 *  Synopsis:
 *		void SCSI_Reset( Lstat lst )
 *
 *  Description:
 *		This command performs a hard reset on the SCSI bus.
 *  In final form, this is only included in the boot level driver.
 *  This allows that durring debugging phase, a problem will not
 *  result in a need to cycle power on the system.  Inside the boot
 *  driver, it performs the valuable service of returning all devices
 *  on the bus to a know state.
 *
 *  Caveats:
 *		Indiscriminant use of the the SCSI BUS RESET can cause problems
 *  for this system as well as others.  Microware defines this as being
 *  a driver for a single initiator environment, in which case we are
 *  the only ones who ever send a hard reset.
 *
 *		This code is used as an extension to init().  If it is included
 *  at boot the _f_sleep() routine is converted to a call to the timer
 *  code.  If it is included for the high level driver, then the code
 *  will call _f_sleep() normally.  The important point is that the calls
 *  to _f_sleep() will fail if the system tick is not running.  This means
 *  that the calls will return without the desired results.
 *
 *		The high level driver will use the timer and code in the timer
 *  interrupt service to perform a SCSI BUS RESET. (irq.c - siop_sge() ).
 */

#if defined (__STDC__) || defined (_ANSI_EXT)
void SCSI_Reset( Lstat lst )
#else
void SCSI_Reset( lst )
Lstat lst;
#endif
{
	MCcICR mccsicr = (MCcICR) &(MCChip->SICR);
	u_int oldmcc;
	u_int32 bitbucket;
	
	/* preserve entry condition of interrupts, then  disable interrupts */
	oldmcc =  (u_int) mccsicr->IEN;
	mccsicr->IEN =   FALSE;		/* disable interrupts from SIOP */
	
	/* send SCSI bus reset */

	ncr_SCSI_reset( lst );		

	/* restore interrupts if they were present */
	if( oldmcc ) {
		mccsicr->ILVL = lst->irqlevel;
		mccsicr->IEN =  TRUE;
	}
}

/*
 *	Function:
 *		seltoirq - SCSI Select Phase Timeout Interrupt Service 
 *  Synopsis:
 *      seltoirq( Lstat lst)
 *
 *  Description:
 *  	This is the interrupt service routine for the select timeout.
 *  There is a problem in the 53C710 that prevents proper select timeouts
 *  from being reliable.  The MCchip Timer 4 is used to generate a software
 *  controlled timeout.  
 *		Algorithm:
 *			if this is out interrupt {
 *			  disable the counter.
 *			  if selection is still in progress
 *               send abort operation to the chip
 *            return serviced
 *			}
 *          return unserviced
 *
 *  See Also:
 *    siop_sto(), dma_abrt(), [irq.c]
 *    initsto(), freesto()
 *
 *  Caveats:
 *		The choise was made to use a timer to create a more general case
 *  timer that would be usable in the booter as well as the runtime 
 *  driver.  It would be possible to use a system state alarm, but that
 *  represents considerable more overhead to the system.
 *
 *  Script Implications:
 *		The script must know of and clear the select in progress flag,
 *  thus preventing the abortion of connections that succeed.   This causes
 *  the need for a one-time patch to the script that can be made to inform
 *  the script of the address of the select in progress flag.
 * 
 */

#if defined (__STDC__) || defined (_ANSI_EXT)
error_code seltoirq( Lstat lst )
#else
error_code seltoirq( lst )
Lstat lst;
#endif
{
#if defined(AUX_TIMER)
	Siop_p const siop = (Siop_p) lst->hdware; /* set hardware pointer */

	MCcICR mcct4icr = (MCcICR) &(MCChip->T4ICR);
	Lthread lth;

#ifndef CBOOT
	extern void _timer();
#endif		

	if( !(mcct4icr->INT) )
		return 1;				/* indicate was not our interrupt */
	
	stop_sto();					/* insure no extra timeouts */

	/* it was our interrupt, proceed */
	if( lst->selflg.sipflag[0] ) {
		/* we are in the process of selecting, tell siop to abort */
		lth = lst->phythread;

#if defined (__STDC__)
		lth->chiperror = EOS_UNIT;			/* mark no unit present */
#else
		lth->chiperror = E_UNIT;			/* mark no unit present */
#endif
		lth->threadstate = TH_DONE;			/* mark done */
		chipreset(lst);

#ifndef CBOOT
		_os_send( lth->processid, SIGWAKE );    /* inform waiting process */
#endif

		lst->chipbusy = CHIPFREE;			/* free chip semaphore */
		reschedule( lst );					/* start SIOP */

	}
#ifndef CBOOT
	else {
		/* not a select timeout, is something else being done? */
		if( lst->chipbusy ) {
			/* yes,  a SCSI BUS RESET is in progress */
			if( lst->chipbusy == DEASERTRST ) {
				/* time to remove B_RST and start a long timer */
				outc( &siop->scntl1, inc( &siop->scntl1 ) & ~B_RST );
				lst->chipbusy = RSTDONE;	/* mark rst deaserted */
				_timer( 0x80000005 );		/* set for 5 seconds */
				chipreset(lst);				/* set up irqs */
				siop_rrst(lst);				/* reset data structures */
					/* does not restart chip yet ... */
			} else {
				/* the 5 second timerout has elapsed, free the bus
				 *  and restart the SIOP.
				 */
				lst->chipbusy = CHIPFREE;	/* free bus */
				reschedule( lst );			/* start SIOP */
			}
		}
	}
#endif /* CBOOT */
#endif
	return SUCCESS;
}


/*
 *	Function:
 *		initsto - initialize the Select Timeout Counter.
 *
 *  Synopsis:
 *		int initsto( Lstat lst )
 *
 *  Description:
 *		Subroutine to initialize the SCSI Select Timout counter.
 *	Timer is conditioned but left disabled.  The interrupt service
 *  is also installed via' F$IRQ.
 * 
 */
#if defined (__STDC__) || defined (_ANSI_EXT)
error_code initsto( Lstat lst )
#else
error_code initsto( lst )
Lstat lst;
#endif
{
#if defined(AUX_TIMER)
	MCcTCR mcct4cr = (MCcTCR) &(MCChip->T4CR);
	MCcICR mcct4icr = (MCcICR) &(MCChip->T4ICR);
	error_code temp;
	u_int32 irqmask;        			/* saved system IRQ level */

	extern void stoirq();				/* interrupt service glue code */

	
	/* add the select timeout ticker to the system irq polling routine */

#ifndef CBOOT
	if (temp = _os9_irq( TVECTOR, lst->irqprior, 
				stoirq, lst, (void *) lst->hdware))
		return temp;
#else
	extern tvsave;							/* storage for the current vector */
	tvsave = setexcpt( TVECTOR, stoirq );
#endif

	/* installation went ok,  now condition the chip but do not enable. */

	irqmask = mask_irq(LEVEL7);			/* insure no interrupts */

	mcct4cr->CEN = FALSE;				/* ensure counter stopped */
	MCChip->T4CMP = SELECTTO;			/* set the compare register */
	MCChip->T4CNT = 0;					/* always start at zero */
	mcct4cr->COVF = TRUE;				/* clear overflow */
	mcct4cr->COC = TRUE;				/* set zero on match */
	mcct4icr->ILVL = lst->irqlevel;		/* set irq level for the timer */

	mask_irq( irqmask );				/* restore the interrupts */
#endif
	return SUCCESS;						/* all went well */
}


/*
 *	Function:
 *		freesto - disable Select timeout ticker.
 *
 *  Synopsis:
 *		int freesto( Lstat lst )
 *
 *  Description:
 *		Subroutine to turn off the SCSI Select Timout counter.
 *	The timer registers are disable and the interrupt level set to 
 *  0 in the MCchip,  making it impossible for the device to fire
 *  an interrupt.
 */
#if defined (__STDC__) || defined (_ANSI_EXT)
void freesto( Lstat lst )
#else
void freesto( lst )
Lstat lst;
#endif
{
#if defined(AUX_TIMER)
	MCcTCR mcct4cr = (MCcTCR) &(MCChip->T4CR);
	MCcICR mcct4icr = (MCcICR) &(MCChip->T4ICR);
	MCcICR mccsicr = (MCcICR) &(MCChip->SICR);

    u_int32 irqmask;		/* saved system IRQ level */

#ifdef CBOOT
	extern int tvsave;
#endif	

	irqmask = mask_irq(LEVEL7);				/* insure no interrupts */

	mcct4cr->CEN = FALSE;					/* ensure counter stopped */
	mccsicr->IEN = FALSE;					/* remove int. enable */
	mcct4icr->ICLR = TRUE;					/* clear pending status */
	mcct4icr->ILVL = 0;						/* remove level */

	mask_irq( irqmask );					/* restore IRQs */
	
#ifdef CBOOT
	setexcpt( TVECTOR, tvsave );			/* restore vector */
#else	
	_os9_irq( TVECTOR, lst->irqprior, 0, lst, 0 );	/* remove from table */
#endif	
#endif
}


/* 
 * Function:
 *       start_sto - start the Select Timeout timer
 *
 * Synopsis:
 *       start_sto( value )
 * Description:
 *       This call activates the Tick timer #4 for use as
 *  a Select timeout register.
 *
 *  Note:  for the non-cboot case of this routine, the value is ignored!
 *
 *
*/

#if defined (__STDC__) || defined (_ANSI_EXT) 
void start_sto( int32 time )
#else
void start_sto( time )
int32 time;
#endif
{
#if defined(AUX_TIMER)
	MCcTCR mcct4cr = (MCcTCR) &(MCChip->T4CR);
	MCcICR mcct4icr = (MCcICR) &(MCChip->T4ICR);
	
	u_int32 irqmask;					/* saved system IRQ level */

	if (time == 0) time = SELECTTO;

	irqmask = mask_irq(LEVEL7);			/* insure no interrupts */

	mcct4cr->CEN = FALSE;				/* ensure counter stopped */
	mcct4icr->ICLR = TRUE;				/* clear pending status */
	MCChip->T4CMP = SELECTTO;			/* set the compare register */
	MCChip->T4CNT = 0;					/* always start at zero */
	mcct4cr->COC = TRUE;				/* set zero on match */
	mcct4cr->CEN = TRUE;				/* start counter */
	mcct4icr->IEN = TRUE;				/* enable interrupts */
	mask_irq( irqmask );				/* restore IRQs */
#endif	
}


/*
 * Function:
 *       stop_sto - stop the Select Timeout timer
 *
 * Synopsis:
 *       stop_sto( void )
 * Description:
 *       This call deactivates Tick timer #4 which is used as
 *  a Select timeout register.
 *
 *
*/
#if defined (__STDC__) || defined (_ANSI_EXT) 
void stop_sto( void )
#else
void stop_sto()
#endif
{
#if defined(AUX_TIMER)
	MCcTCR mcct4cr = (MCcTCR) &(MCChip->T4CR);
	MCcICR mcct4icr = (MCcICR) &(MCChip->T4ICR);
	
	u_int32 irqmask;					/* saved system IRQ level */

	irqmask = mask_irq(LEVEL7);			/* insure no interrupts */

	mcct4icr->IEN = FALSE;				/* disable interrupts */
	mcct4cr->CEN = FALSE;				/* stop counter */
	mcct4icr->ICLR = TRUE;				/* clear pending status */

	mask_irq( irqmask );				/* restore IRQs */
#endif
}	

/*
 * Function: 
 *      _timer - private timer entry point for high level driver
 *
 * Synopsis:
 *		void _timer( time )
 *
 * Description:
 *		Time otherwise describes the time that will used to "sleep".
 *  In this case,  the timer is set and we hang out here until the
 *  timer goes off.
 *
 *  time is treated as ticks (10msec) or seconds based on bit 32 of the
 *  value passed.
 *
 */
#if defined (__STDC__) || defined (_ANSI_EXT)
void _timer( int32 time )
#else
void _timer( time )
int32 time;
#endif
{
	if( time < 0 )
		time = (time & 0x7FFFFFFF) * 1000000;		/* seconds */
	else
		time *= 10000;								/* msecs */

	start_sto( time );								/* starts the timer */
 }

#ifdef CBOOT
/*
 * Function: 
 *		_f_sleep - model of the system sleep service routine.  (CBOOT)
 *
 * Synopsis:
 *		int _f_sleep( time )
 *
 * Description:
 *		This is this drivers model of the F$Sleep service call.
 *		If time == 0 then this routine delay a bit and return.  The only
 *	routine that should be calling in this manner is enqueue() which
 *  will simply re-call this routine until the current thread completes.
 *		Time otherwise describes the time that will used to "sleep".
 *  In this case,  the timer is set and we hang out here until the
 *  timer goes off.
 *
 */

#if defined (__STDC__) || defined (_ANSI_EXT) 
error_code _f_sleep( int32 time )
#else
error_code _f_sleep( time )
int32 time;
#endif
{
 	extern struct lstat sstorage;
 	extern u_int32 ttimer,ttimerdone;
 	
 	if( time == 0 )
		for( time = 0; time < 1000; time++ );
   	else {
		ttimer = TRUE;
 		if( time < 0 )
	 		time = (time & 0x7FFFFFFF) * 1000000;		/* seconds */
 	 	else
			time *= 10000;								/* msecs */

		start_sto( time );
		while( !ttimerdone );				/* wait for timer */
 		ttimer = FALSE;						/* clear timer mode */
 		ttimerdone = FALSE;					/* clear done flag */
 	}
}

#endif
		
/****
 **  Below is a series of subroutines that have been coded in
 **  assembly for various reasons.  Obviously they are entirly
 **  machine specific at least to the Motorola MC68xxx family
 **  of processors.  
 ****/

#ifdef _UCC
_asm(" use <dv162asm.a>");
#else
@ use <dv162asm.a>
#endif

#ifndef CBOOT
#ifdef DEBUG

#ifdef _UCC
_asm(" use <dbg16x.a>");
#else
@ use <dbg16x.a>
#endif

#endif /* DEBUG */

#ifdef _UCC
_asm(" use <nbt16x.a>");
#else
@ use <nbt16x.a>
#endif

#else /* CBOOT */

#ifdef _UCC
_asm(" use <cbt16x.a>");
#else
@ use <cbt16x.a>
#endif

#endif /* CBOOT */

