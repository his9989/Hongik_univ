<code>

            .section        ".text"
    fmt:    .asciz  "%d %s %c %d %d %d\n"
            .align 4

            .global main, printf
    main:   save    %sp, (-104-(N*4))&-8, %sp
            mov     %g0,    %l2
            set     records, %l0
            mov     N, %l1
            sll     %l1, 2, %l1
            sub     %fp, %l1, %l1
            ba      test
            nop

    loop:   sll     %l2, 5, %l3
            sll     %l2, 2, %l4
            add     %l0, %l3, %o0
            add     %l1, %l4, %o1
            st      %o0, [%o1]
            inc     %l2
            nop

    test:   subcc   %l2, N, %g0
            bl      loop
            nop

    func:   mov     N, %o0
            mov     %l0, %o1
            call    avg
            nop
            mov     N, %o0
            mov     %l0, %o1
            mov     %l1, %o2
            call    sort
            nop
            mov     %g0, %l2
            ba      printtest
            nop

    printloop:      sll     %l2, 2, %l4
                    add     %l1, %l4, %l4
                    set     fmt, %o0
                    ld      [%l4], %l5
                    lduh    [%l5], %o1
                    add     %l5, 2, %o2
                    ldub    [%l5+19], %o3
                    ld      [%l5+20], %o4
                    ld      [%l5+24], %o5
                    ld      [%l5+28], %l6
                    st      %l6, [%sp+92]
                    call    printf
                    nop
                    add     %l2, 1, %l2

    printtest:      subcc   %l2, N, %g0
                    bl      printloop
                    nop
                    ret
                    restore

    avg :   save    %sp, -96, %sp
            mov     %g0, %l2
            ba      avgtest
            nop

    avgloop :       sll     %l2, 5, %l0
                    add     %i1, %l0, %l1
                    ld      [%l1+20], %l3
                    ld      [%l1+24], %l4
                    add     %l3, %l4, %l5
                    srl     %l5, 1, %l5
                    st      %l5, [%l1+28]
                    add     %l2, 1, %l2

    avgtest:        subcc   %l2, %i0, %g0
                    bl      avgloop
                    nop
                    mov     %l2, %i0
                    ret
                    restore

    sort:   save    %sp, -96, %sp
            mov     %g0, %l0
            sub     %i0, 1, %l7
            ba      sorttest
            nop

    sortloop:       add     %l0, 1, %l0
                    mov     %g0, %l2
                    mov     %g0, %l1
                    ba      sorttest2
                    nop

    sortloop2:      add     %l1, 1, %l1
                    sll     %l2, 2, %l3
                    add     %i2, %l3, %o0
                    add     %o0, 4, %o1

                    ld      [%o0], %o2
                    ld      [%o1], %o3
                    ld      [%o2+28], %l5
                    ld      [%o3+28], %l6
                    call    printf
                    nop

                    subcc   %l5, %l6, %g0
                    bg      change
                    nop
                    add     %l2, 1, %l2

    sorttest2:      subcc   %l1, %l7, %g0
                    bl      sortloop2
                    nop

    sorttest:       subcc   %l0, %l7, %g0
                    bl      sortloop
                    nop
                    mov     %g0, %i0
                    mov     %g0, %i1
                    mov     %g0, %i2
                    ret
                    restore

    change: sll     %l2, 2, %l3
            add     %i2, %l3, %o0
            add     %o0, 4, %o1
            ld      [%o0], %o2
            ld      [%o1], %o3
            st      %o3, [%o0]
            st      %o2, [%o1]
            ba      sorttest2
            add     %l2, 1, %l2
        
</code>
