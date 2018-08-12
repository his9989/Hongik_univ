<code>
            .global main
    main:   save    %sp, -96, %sp
            mov     %g0, %o1
            mov     1, %o2
            mov     1, %o3
            mov     3, %l0

    loop:   subcc   %l0, N, %g0
            bg      next_r
            nop
            add     %o1, %o2, %l1
            add     %l1, %o3, %l1
            mov     %o2, %o1
            mov     %o3, %o2
            mov     %l1, %o3
            mov     %l1, %o0
            nop
            inc     %l0
            ba      loop
            nop

    next_r: ret
            restore
</code>
