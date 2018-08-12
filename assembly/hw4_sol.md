<code>

            .section        ".bss"
    buffer: .skip   320

            .section        ".text"
    Buffer = 320

            .align  4
    fmt:    .asciz  "%d %d %d\n"

            .align  4
            .global main
    main:   save    %sp, (-Buffer-96)&-8, %sp
            mov     %g0, %l0        ! i for loop
            mov     %g0, %l1        ! char num
            mov     %g0, %l2        ! word num
            mov     %g0, %l3        ! line num

    open:   ld      [%i1+4], %o0
            mov     %g0, %o1
            mov     5, %g1
            ta      0
            mov     %o0, %l7        ! file discripter move for %l7

    read:   set     buffer, %o1
            mov     Buffer, %o2
            mov     3, %g1
            ta      0               ! return value is number of input bite

    close:  mov     %l7, %o0
            mov     6, %g1
            ta      0
            ba      test
            nop

    loop:   set     buffer, %o3
            ldub    [%o3+%l0], %l5
            subcc   %l5, 32, %g0    ! if space
            be      count_space
            nop
            subcc   %l5, 10, %g0    ! if line change
            be      count_line
            nop
            subcc   %l5, 65, %g0    ! word
            bge     count_word
            nop
            subcc   %l5, 48, %g0
            bge     count_number
            nop

    test2:  add     %l0, 1, %l0

    test:   subcc   %l0, Buffer, %g0
            bl      loop
            nop
            set     fmt, %o0
            mov     %l1, %o1
            mov     %l2, %o2
            mov     %l3, %o3
            call    printf
            nop
            mov     %g0, %l0

    open2:  ld      [%i1+8], %o0
            mov     2, %o1
            mov     5, %g1
            ta      0
            mov     %o0, %l7

    write:  set     buffer, %o1
            mov     Buffer, %o2
            mov     4, %g1
            ta      0

    close2: mov     %l7, %o0
            mov     6, %g1
            ta      0
            ret
            restore

    count_space:
            subcc   %l0, 0, %g0
            be      test2
            nop
            sub     %l0, 1, %l0
            ldub    [%o3+%l0], %l4
            add     %l0, 1, %l0
            subcc   %l4, 32, %g0
            be      test2
            nop
            add     %l2, 1, %l2
            ba      test2
            nop

    count_line:
            add     %l3, 1, %l3
            ba      test2
            nop

    count_word:
            subcc   %l5, 90, %g0
            ble     add_char
            nop
            subcc   %l5, 97, %g0
            bl      test2
            nop
            subcc   %l5, 122, %g0
            ble     swap
            nop
            ba      test2
            nop

    count_number:
            subcc   %l5, 57, %g0
            ble     add_char
            nop
            ba      test2
            nop

    swap:   sub     %l5, 32, %l5
            stb     %l5, [%o3+%l0]
            add     %l1, 1, %l1
            ba      test2
            nop

    add_char:
            add     %l1, 1, %l1
            ba      test2
            nop

</code>
