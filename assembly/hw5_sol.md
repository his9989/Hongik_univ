<code>

    hw5 1.1 2.2 3.3 4.4 5.5
    10진수 값 : 8.158
    16진수 값 : 402050cd

</code>

### $ cat hw5.s

<code>

    fmt:    .asciz  "10진수 값 : %0.3f\n"
    fmt2:   .asciz  "16진수 값 : %x\n"

            .align  4
            .global main, printf
    main:   save    %sp, -120, %sp
            mov     0, %l0
            st      %l0, [%fp-8]
            ld      [%fp-8], %f2
            fitod   %f2, %f2
            std     %f2, [%fp-8]            ! %f2, %f3이 %fp-8부터 8비트에 저장

            ld      [%i1+4], %o0
            call    atof
            nop
            fmuld   %f0, %f0, %f0           ! %f0 제곱
            ldd     [%fp-8], %f2
            faddd   %f0, %f2, %f2
            std     %f2, [%fp-8]
            nop

            ld      [%i1+8], %o0
            call    atof
            nop
            fmuld   %f0, %f0, %f0
            ldd     [%fp-8], %f2
            faddd   %f0, %f2, %f2
            std     %f2, [%fp-8]
            nop

            ld      [%i1+12], %o0
            call    atof
            nop
            fmuld   %f0, %f0, %f0
            ldd     [%fp-8], %f2
            faddd   %f0, %f2, %f2
            std     %f2, [%fp-8]
            nop

            ld      [%i1+16], %o0
            call    atof
            nop
            fmuld   %f0, %f0, %f0
            ldd     [%fp-8], %f2
            faddd   %f0, %f2, %f2
            std     %f2, [%fp-8]
            nop

            ld      [%i1+20], %o0
            call    atof
            nop
            fmuld   %f0, %f0, %f0
            ldd     [%fp-8], %f2
            faddd   %f0, %f2, %f2
            std     %f2, [%fp-8]
            nop

            ldd     [%fp-8], %f2
            fsqrtd  %f2, %f2
            nop
            st      %f2, [%fp-12]
            ld      [%fp-12], %o1

            set     fmt, %o0
            call    printf
            nop

            ld      [%fp-12], %o1
            set     fmt2, %o0
            call    printf
            nop

            ret
            restore

</code>
