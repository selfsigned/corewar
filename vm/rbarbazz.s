.name "zork"
.comment "I'M ALIIIIVE"    #yeeeet

start:
add r1, r2, r3
aff r3
sub r3, r1, r5
aff r5
live %-1
ld 987987987, r8
aff r8

#fork %782951
#st r1, r2
#st r2, 55654654654654
#live:live %-1
#add r1, r2, r2
#aff r2
#ld 9879871, r3
#aff r3
#lld %-9, r4
#aff r4
#lldi %-3, %3, r5
#aff r5
#dab:
#ldi -65498775, %-1649845456210, r7
#aff r7
#st r2, :dab
 #sti r1, %5, %10
#add r6, r6, r6 #carry -> 1
#zjmp %:dab


#l2:
#		sti r1, %:live, %1
#		and r1, %0, r1

#live:	live %1

#add r1, r3, r1
#add r1, r3, r1
#add r1, r3, r1
#dab:
#add r1, r3, r1
#aff r1
#add r1, r3, r1
#aff r1
#add r1, r3, r1
#aff r1
#add r1, r3, r1
#aff r1
#add r1, r3, r1
#aff r1
#		sub r5, r6, r7
#live %1
#zjmp %:live
