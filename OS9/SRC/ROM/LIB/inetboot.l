ޭ��       �f	:         >        ����            inetboot.c    	TS     �bpt_test     inetboot     msgprint      net_in       net_inpbuf      net_outbuf     save_bootp     stash_ipaddr    *GOTBOOTP  %4u.%u |  %d one-thousand... inetboot: timer test finished  inetboot: start 5 sec timer test inetboot: msgpcntl=%x:16, ttcntl=%x:16 inetboot: (Edition %d) using %s MTU=%d inetboot: Bootp/Tftp sequence try: %d/%d H�Àp 0. r��c& .  r
a   ,  .  r
a   / A��� "a   X�L��NuH�_� @v G�  E� a   p/ C� 	r a   p 0. J�X�gV|a�C��� 	a   (.  p2*ڀ`( r ЀҀ�Ҁ Ё��  fa �bC��� 	"R�a   ��  b�a �JC��� 	a   a �<p 0( / /( C��� 	ra   a � /
C��� 	"a    "h XN�C� H�� R�p 0.  J�ga ��p/ E��� 
"a   X� a   J�fp��m� $h \N�a    <  `  �p/ r$ ЁE� "
a   p/  	E� "
a   p 0.  r	�-@  a   , P�fp 0.  /  ".  a   , X�g,J�  gJ�  g .  ".  a   B�  B�  J�gp��m �: "h \N�a   J�fDp/ C� 	C��8"	a   p/ C� 	C� "	a   C�  -I-H-n  A� a,P�Hx A�  r a   Hx A� r a   P� L��NuH� � y    !@�L� Nu      VectTbl     8  0__udivide     �   �__umodulo     �  bootp     �  
bootram     0  t 0  � 0  � 0  �bootsize     0  \ 0  �bprp     0  8 0  H 0  � 0  �bpt_curtick     0   � 0   0  ` 0  | 0  �bpt_init     �  2bpt_term     �    �  �getbootmem     �  `in_bootsize     0  T 0  linsert     �  �memcpy     �  > �  N �  � �  �memset     �  B �   �  memsize     0  � 0  � 0  �rprintf     �   �  \ �  � �  � �  � �  � �  tftp     �  x    0   0   0  � 0  � 0  � 0  � 0  � 0  � 1  � 1  H 0  : 1  . 1  * 1   �                ޭ��       �f	:    �     	B        ����            lbootp.c    	TRYCNT      WAITCNT     bootp    bprp      getvend_1048    �in_bootsize      inetname    make_bootp    vshow_ether    �..but not for my ethernet address! GOT BOOTP RESPONSE from server %s! done.  bootp: recv wait %d for %d ticks (10/second) ..but not my xid number! (expected %x, got %x) bootp: got UDP packet src=%08x:%d dst=%08x:%d  * %u.%u.%u.%u %x:%x:%x:%x:%x:%x <<no subnetmask tag>>  My subnet mask is: %s  My tftp bootfile is: %s  bootp: delay 10 seconds... bootp: Exiting after %d trys My IP address will be: %s (0x%08x) bootp: error - bootfile size is zero bootp: Error or timeout .. Retry request My bootfile size is: %d (512-byte) blocks  bootp: %s broadcasting for server..try %d/%d bootp: fatal error - no bootsize tag in BOOTP record bootp: fatal error - no bootfile name in BOOTP record  H�A� @p ( / p ( / p ( / p ( / p ( / p / A�2 A���"a   A�2 �� L��NuNU  H�A�A� J� fC�r 	C���"	a   `2p ( / p ( / p ( / p / A�r A���"a   �� A�r L��N]NuNU��H�� @"AB���$HHx,r a    
a   J�X�fp/ r 
Ё"	a   X�p/ A��� T�"	a   � |  |   -��-@  -@  %@  .  r
a   5@ | c �| � �| S �| c � <  ,X�L��N]NuNU��H�� @I� * ~0"҇a �F& B� $p�!@ Hx z +E��"L R�J�g6 .  Ѯ  #n   ��  o"p 0.  J�ga   E��� 
".  a   p ` p 0.  J�g$a   p�� 	a �""@/.  /E��z 
"	a   P�//pC/  rDa   p<ѭ��| �� R�p 0.  r��ea   /-��C��h 	"a   X�p/  C���"	"n  N�$@ 
X�f~$R�p��op$ ".   剐��Ё牐�剐��Ё�ЁrЁ"<  a   r 2 -A  p��hF@�n H�r ЀҀ�Ҁ +@��p 0.  r��e ��a   C��L 	a   ` ��p&J��"KP�p 0rC��fp 0+ rD��g:p 0.  r��e �a   p 0+ / /* p 0/ G��� "* a   �� ` ��p/ E��� 
~"	҇a   p 0.  J�X�g&a   p/ E���Y�&O&�a ��$@G�� "
a   P�p/ r 	Ё~0"҇a   J�X�gp 0.  J�g ��a   E��� 
a   ` �n .  �� g(p 0.  J�g �Xa   /) E��� 
".  a   X�` �<Hx,E�  
"	a   p/ E��� 
~"	҇a   p 0.  J�P�g,a   p/ E���Y�&O&�a �8$@/) G��� "
a   �� p ) lJ�g p 0.  J�gXa   E��" 
~l"	҇a   `Bp 0.  J�ga   E��Z 
a   p 0.  r��ea   E�� 
a   pdЮ  ��  b�`  �Hn E� � 
ra 6J�X�f@p 0.  J�ga   E��� 
a   p 0.  r��ea   E��� 
a   pdЮ  ��  b�`Hp 0. J�f^p 0.  J�ga   E��� 
a   p 0.  r��ea   E��` 
a   pdЮ  ��  b�p 0.  r��e �8a   E��8 
a   ` �&p 0.  J�ga   A��� r 2. a   Hm��A� � raZJ�X�g2p 0.  J�g@a   p/ A���Y�$O$�a �� @E��� 
"a   P�`p 0.  J�ga   A��n a    	L��N]NuNU  H�� @"m z p@$H��p rc��f&p ( �   �fp ( rS��fp ( rc��gp `LX�`6p H�H���fR�p J�gp , J�g/ 	"a   X�`��p , ��bp �   �f� L��N]Nu         TS     �  p �  � �  � �  | �  � �   �  T �  | �  � �   �  ( �  B �  � �  � �  � �  � �   �  ( �  Z �  �__smodulo     �  F__udivide     �  �bpt_bootp     �  �bpt_curtick     0  � 0  R 0  V 0  � 0  � 0  � 0  �bpt_rseed     0  � 0   0  N 0  Xmemcmp     �  >memcpy     �  � �  � �  � �  � �  � �  	memset     �  �msgprint     0  h 0  � 0  � 0  p 0  � 0  � 0  J 0  r 0  � 0    0    0  8 0  x 0  � 0  � 0  � 0    0    0  R 0  �net_in     0  net_outbuf     0  $rprintf     �  ~ �  � �  � �  � �  � �  ( �  ^ �  � �  � �   �  2 �  L �  � �  � �  � �  � �   �  8 �  z �  �rsprintf     �    �  bstrcpy     �  2udp_out     �  �    0  4 0  � 0  ` 0  � 0  � 0  f 1  � 1  z 1  ` 0  Z 0  V 0  R 0  � 0  j 0  V 0  & 0   0  �                ޭ��       �f	:           X        ����            lip.c    	b_check    �check16    6icmp_check    2icmp_in    �in_checksum    �ip_inp     �ip_out    �udp_in    udp_out    \  %02x   ICMP  %%frag!  %%runt!  %%header!  %%version! IP OUT:   data= IP INP:   data= %%checksum ip! %%checksum udp!  IP INP: rlen=%d  %%checksum icmp! type = %d, code = %d  IP OUT: dest=%08x len=%d IP OUT:frag req! len=%d, mtu=%d  NU  H��(@ A*- "Hp 0.  r��ea   E��f 
"a   p��lp 0.  r��e  �a   E���`  �< ��r  �p��gp 0.  r��exa   E���`hp�r  �/p "	a >r 2 J�X�gp 0.  r��eDa   E���`40<��i r 2 J�f0<  �i r 2 J�g p 0.  r��ea   E��@ 
a   p ` p 0.  r��e  �$Ia   G��X a   | G�� r 2h a     g
G��� a   R�p��m�G��� a   p 0.  r��eBa   G��
 a   `"G��� r 2h a     g
G��� a   R�p ��m�E��� 
a   p ) 	�   g
�   g`/ "a^X�` X/ "a VX�` Hp�` BNU  H�� @"A<- 
z  gp/ p "a \: X�p 0/ p 0"	a �F@X�L��N]NuNU  H��&@ A*- "Hp�r  �$H��p 0.  r��ea   I��� a   p�r  �,��/p "
a �nr 2 J�X�gp 0.  r��e
I��* a   p `  �p 0.  r��ep * / I�� r a   X�p �   fB ) #i  #@ `r  J�g$Bj /p "
a ��5@ p/ / "a  ��� p 0.  r��e
A�� a   pL��N]NuNU��H�� A - "Hr�~ ���$Hr�~ �" �� r��dp 0.  r��e`A���`T+i ��+i ��B-��| ��;j ��p 0* J�g8p 0* / A��� "
a �:r 2 J�X�gp 0.  r��e
A��� a   p `pL��N]NuNU  H�� @"A*- 0- r��$EE� *
� EB) 2.  Rn  3A Bi | � @ 	3E #h $ #h H Bi 
p�r  �/p "	a ��3@ 
p 0( ��X�c,p 0.  r��e  �a   p 0( / E��� 
"a   X�`  �p 0.  r��ea   /E��N 
") a   X�p 0.  r��e  �$Ia   G��� a   | G��h r 2h a     g
G��P a   R�p��m�G��F a   p 0.  r��eBa   G��` a   `"G�� r 2h a     g
G�� a   R�p ��m�E��� 
a   /) / "	"h `N�P�L��N]NuH�A� @p r�~ ���r �   fr L��NuNU��H�� @0- 
"m &m Q�$I4�5@ C� ,	5F Bj +h $��+h H��B-��| ��;F��/C��� 	"
a �
5@ p/ / "
a ���� L��N]NuNU��H�� A<- 
Bm��r 2�/r 2  "aB: 0@ r 2 J�X�g&p 0S�r 0 �I�m��p/ p 0A���"a: X� L��N]NuH� � A$/ S�< 2�AQ����A�AL�Nu     TS     �   �  8 �  b �  � �  � �  � �  > �  * �  : �  d �  � �  �msgprint     0  
 0  , 0  X 0  � 0  � 0  � 0  4 0    0  \ 0  x 0  � 0  : 0  � 0  . 0  Z 0  | 0  �rprintf     �    �  � �  � �   �   �  . �  H �  Z �  j �  | �  4 �  l �  � �  � �  � �  N �  t �  � �  � �  � �  � �  � �  � �   �      1  � 1  �                ޭ��       �f	:           L        ����            larp.c    arp_dest_hwaddr       arp_dest_ip      arp_input     arp_resolve    �arp_whohas    2������  NU��H�� @"A$Ip&I��| p/ I��� ~"҇a   p 0+ r��X�f  � -���� $f  �p/ r Ё"P�a   p/  P�~0"҇a   p/ r Ё~"҇a   p/ r ЁI���"a   7|  p/  
~"҇a   p/  
\�"P�a   5| p/ p*�� 	r a   p</  "
"h dN���  `>p 0+ r��f2p/ r ЁA� "a   J�X�fp/ A�   P�"a   p, X� L��N]NuNU�RH�� @+A�RC��Vp$I��p*/  	r a   p/  	G���"a   p/  	\�~0"҇a   3| 4� 5|  |  |  5|  p/  
P�~0"҇a   p/ r 
Ё~$"҇a   p/ p�� 
C��R"	a   p*/  C��V"	"h dN��� L��N]NuNU��H�� @,pd+@�� r���g2�� g$-F  "a �p/  C���"	"n  N�J�X�g�A�   `A��� L��N]Nu   memcmp     �  memcpy     �   0 �   ^ �   p �   � �   � �   � �   � �    �  d �  v �  � �  � �  �memset     �   � �  Tnet_in     0  ,    0  8 0   0   0   0                  ޭ��       �f	:    d     �        ����            ltftp.c    dummy       make_tftp_ack    Nmake_tftp_req    dtftp    �%s  tftp: RRQ %d %d  \  -  /  |  %d:%d octet  blocks (%dKb) Unknown transfer ID tftp: Block received: %d tftp: fetching %d blocks tftp: DUP %d (expected %d) tftp: expected %d: received   tftp: timeout .. try: %d/%d  tftp: Recv wait, Timeout=%d  tftp: ICMP trouble! Aborting tftp: stale server %s port %d  tftp: server response %s port %d tftp: timeout count exceeded .. giving up  tftp: error from server: (%d:%s) aborting! tftp: NON-CONNECTED server response %s port %d tftp: got UDP src=%08x:%d dst=%08x:%d rewaiting  tftp: New Server Mode assumed, Transfer accepted.  H�� @0� 1A pL��NuNU  H�� A"m $m 2�r��f 
3@ &IX� "a    `  	T�&@"a    a   ��B "
a    
a   ��B�� L��N]NuNU��H�?�( +A��;m 
 z|EB���p+@��B���A� .$A�^+H��B���Bm��p 0.  J�ga   A��\ r 2- a   Hz�/pA� l"a �2& p 0.  r��P�ea   A��� r a   //pE/  A�OX"a   p2+@��p+@���� p 0.  r��ea   A��X "-��a   p/  A���" n  N� @ X�f  �p"-��Ҁ+A��p��op 0.  J�g a   C���`  �p 0.  J�gJ���fp 0.  r��ea   p/ C��� 	"-��a   X�p2+@��p 0.  r��ea   C��� 	"S�a   //p 0/  C�OX"	` � a   J�g p 0.  r��e �a   C��� 	a   ` rp"H��$IP�iOX g2p 0.  r��e ��a   p 0) / /( p 0/ I��< "( `  J���f  �p�Rfp 0.  r��e `  �p�Rf @p�j f 6+h ��<;F��p/ I��� ~"҇a   p 0.  J�X�g.a   p/ G���Y�(O(�a   &@p 0/ I�� "a   ��  -�ְ� f0-�ڰQgTp/ I��� ~"҇a   p 0.  r��X�e  �a   p/ G���Y�(O(�a   &@p 0/ I�� "a   �� `tp�Rf,p 0.  J�g *a    
X�/ I��� 8j "a   X�` 
&E�� f0p 0) (@I���+L��/-�� -��"
X�a    -��ѭ��R�X�` 8j ��o  �p/ /-��I��"a �6& p 0.  r��P�ea   I��� "S�a   //-��p 0/  C�OX"	a   p/ C��� 	r��"a   p 0.  r���� e ��a   p/ A���Y�"O"�a    @p 0/ C��n 	"a   �� ` ��p 0.  r��ea   /A��� 0j "a   X�p 0.  r��ea   A�� "S�a   //p 0/  A�OX"a   �� ` �X B2j  	0� 1@ p& p 0.  r��ea   A��� "S�a   p/ /p 0/  A�OX"a   p2+@��B���B���p 0.  r���� ea   A��� "S�a   `4p 0.  J�g*A��V "-��R����A�  .0 "a   p����lB����   ��g ��p+@��J���g  �S�p 0.  r��ea   A��� r 2- a   J���g8A� ����/ -��r a   p 0.  r��X�eB/-��A��� "S�a   X�`,p 0- R���fS�p+@��p 0.  r��eA��� "a   p 0.  r��eA��� "lR��a   p����fp 0.  r��ea   A��j a   p 0- ��g <   �`r  ` <   �L��N]Nu   "            TS     �   �  F �  � �  � �  � �  $ �  d �  � �   �  | �  � �  B �  � �  � �  � �  D �  � �  � �  �bprp     0  ,icmp_check     �  Ninetname     �  * �  � �  �memcpy     �   �  h �   �  |memset     �  &msgprint     0   0  : 0  | 0  � 0  � 0  � 0   0  X 0  � 0  � 0   0  n 0  � 0  6 0  � 0  � 0  � 0  : 0  ~ 0  � 0  � 0  , 0  d 0  | 0  �net_in     0  �rprintf     �    �  R �  � �   �  2 �  n �  > �  � �  � �  P �  � �  � �   �  R �  � �  � �   �  F �  v �  � �  �strcpy     �  � �  � �  �strlen     �  � �  �udp_out     �  f �  h �   �  j    1  � 0  � 0  �                                 ޭ��       �f	:           F        ����            ethernet_in.c    ethernet_in     ^ETHER_IN: type=%04X (IP) ETHER_IN: type=%04X (ARP)  ETHER_IN: %04X <---unknown ETHER type! NU  H�� @"A(- E�  /	 G�  "&h hN�, X�fp `  �p 0* �   g8�  fhp 0.  r��ea   G��d r 2* a    G�  "a   * `Xp 0.  r��ea   G�� r 2* a   p��/ G� "a   * X�` p 0.  r��ea   G�� r 2* a   ��gp��f �<A�  L��N]Nu       TS     �   � �   � �  arp_input     �   �ip_inp     �  msgprint     0   � 0   � 0  net_inpbuf     0   p 0   x 0   � 0   � 0  :rprintf     �   � �   � �  *                    