<code>

            .global main
    main:   save    %sp, -96, %sp
            mov     N0, %o1
            mov     N1, %o2
            mov     N2, %o3
            mov     N3, %o4
            mov     0, %o5
            mov     0, %l3
            mov     0, %l4
            sll     %o1, 24, %o1
            sll     %o2, 24, %o2
            sll     %o3, 24, %o3
            srl     %o1, 24, %o1
            srl     %o2, 24, %o2
            srl     %o3, 24, %o3
            sll     %o4, 24, %o4
            sll     %o3, 16, %o3
            sll     %o2, 8, %o2
            or      %o2, %o1, %l0
            or      %o3, %l0, %l0
            or      %o4, %l0, %l0
            mov     %l0, %l1
            mov     %l0, %l2

    testa:  cmp     %o5, 15
            bg      testb
            nop
            btst    2, %l1
            be      cleara
            nop
    seta:   inc     %l3
            inc     %o5
            ba      testa
            srl     %l1, 2, %l1
    cleara: srl     %l1, 2, %l1
            ba      testa
            inc     %o5

    testb:  cmp     %o5, 0
            ble     finish
            nop
            btst    1, %l2
            be      clearb
            nop
    setb:   inc     %l4
            sub     %o5, 1, %o5
            ba      testb
            srl     %l2, 2, %l2
    clearb: srl     %l2, 2, %l2
            ba      testb
            sub     %o5, 1, %o5

    finish: cmp     %l4, %l3
            bg      finl
            nop
            sub     %l3, %l4, %o0
            ba      next_r
            nop

    finl:   sub     %l4, %l3, %o0
            ba      next_r
            nop

    next_r: ret
            restore

</code>
