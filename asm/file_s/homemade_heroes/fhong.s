.name       "fhong's love"
.comment    "Do nothing but nothing~"
start:
    st      r1, -20
    ld      %47251452, r4
    st      r4, -42
    ld      %17563649, r5
    st      r5, -50
    ld      %500, r6
    ld      %151011840, r7  
    ld      %1057554495, r8
    ld      %17825783, r9
    st      r1, 6
    live    %123
fork_factory1:
    fork    %:hospital1
    or      %0, %0, r16
    fork    %:fork_factory2
    zjmp    %:fork_factory1
hospital1:
    st      r1, 6
    live    %123
wall1:
    ld      %:start, r2
    sub     r2, r6, r2
    sti     r7, r2, %0
    sti     r7, r2, %0
    sti     r7, r2, %0
    sti     r7, r2, %0
    sti     r7, r2, %0
    sti     r7, r2, %0
    sti     r7, r2, %0
    sti     r7, r2, %0
    sti     r7, r2, %0
mess_up_army1:
    sti     r1, r1, %500
    sti     r7, r3, %500
    ld      %0, r14
    zjmp    %:mess_up_army1
hospital2:
    st      r1, 6
    live    %123
    st      r1, 6
    live    %123
    st      r1, 6
    live    %123
    st      r1, 6
    live    %123
    st      r1, 6
    live    %123
    st      r1, 6
    live    %123
    st      r1, 6
    live    %123
fork_factory2:
    st      r1, 6
    live    %123
    or      %0, %0, r16
    fork    %:mess_up_army1
    fork    %:hospital2
    zjmp    %:fork_factory2
wall2:
    ld      %:end, r3
    add     r3, r6, r3
    sti     r7, r3, %:end
    sti     r7, r3, %:end
    sti     r7, r3, %:end
    sti     r7, r3, %:end
    sti     r7, r3, %:end
    sti     r7, r3, %:end
    sti     r7, r3, %:end
    sti     r7, r3, %:end
    sti     r7, r3, %:end
    or      %0, %0, r16
    zjmp    %:mess_up_army1
end:
