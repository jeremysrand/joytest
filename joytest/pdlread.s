;
;  pdlread.s
;  joytest
;
;  Created by Jeremy Rand on 2020-06-09.
;  Copyright © 2020 Jeremy Rand. All rights reserved.
;
      .include        "apple2.inc"
      .export         _pdlRead


; ROM entry points

PREAD   :=      $FB1E   ; Read paddle in X, return AD conv. value in Y

_pdlRead:
        bit     $C082           ; Switch in ROM
        tax                     ; Set paddle number
        jsr     PREAD           ; Read paddle value
        tya
        ldx     #$00
        bit     $C080           ; Switch in LC bank 2 for R/O
        rts
