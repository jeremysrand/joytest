joytest
=======

This is a joystick test program for the cc65 joystick driver.  A problem was found with the original cc65 driver so it has being re-written by Oliver Schmidt.  I am creating this program to provide feedback on the new implementation when run on a variety of HW.  I have access to an Apple //e and an Apple //gs, each with a CH brand joystick attached.  By making this program available, I am hoping to get feedback from more of the community and get coverage of other HW.  Please download the disk image to assist in getting greater coverage of this new joystick driver:

[Download a disk image](https://github.com/jeremysrand/joytest/releases/download/0.6/joytest.dsk)

When run, the screen shows the current state of the joystick as read by the cc65 driver.  The direction of the joystick (if any) and the state of the two buttons is displayed.

If you have an accelerator, you may want to disable it.  For systems that shipped running at greater than 1MHz (like the //gs and the //c+), testing at 1MHz and at accelerated speed is useful.  Feel free to provide feedback about the behaviour of the driver on a machine with an optional accelerator card active.  Although this information is interesting, I don't think the cc65 project intends to add any support for accelerator detection and handling.  Most important is to show that it works acceptably at the speed(s) supported by the platform as it originally shipped.

There are a series of tests that are worth running.

Basic Operation:
--------------------

For this test, just manipulate the joystick and ensure that the motion of the joystick is reflected on the screen.  Press each button and make sure that the appropriate button number highlights.  Make slow and deliberate movements as well as fast movements with the joystick and ensure that the changes on the screen reflect those motions.

X Axis Test:
--------------

In this test, we will focus on the X axis.  Start with the joystick in the centre and slowly push the joystick to the right.  At some point, you should notice the display change to indicate the joystick is in the right position.  Note the position of the joystick when the screen position changes.  Continue pushing to the extreme right and then slowly return to the centre, again noting where the position changes back to centre.  Check to see that these are reasonable positions on your joystick for when centre changes to right and back again.  Is it far enough from the centre and not too close to the extreme right edge?  Try doing the above with the joystick pressed up, moving from up to upper right and then back to up position.  And again with the joystick down, moving to the right and back to centre.  In all tests, the joystic position on the screen should be consistent and reflect the physical positon of the joystick.

Do the same again except this time move from the centre to the left and then back to the centre.  Be sure to try motions to the left with the joystick also pressed all the way up and down.

Y Axis Test:
--------------

This is essentially a repeat of the tests described for the X axis except this time we will slowly be pushing the joystick up and then down and watching the thresholds in that direction.  Redo the same kinds of motions you performed on the X axis except for up and down.

Second Joystick:
--------------------

If you have a second joystick, it can be tested also.  Press 2 to switch to the second joystick (1 returns you to the first joystick).  Then repeat all of the tests described above except with this joystick.

Issues Or Feedback:
------------------------

If you encounter any oddities or your thresholds from the X axis or Y axis tests are problematic, please contact me or raise an issue against this project on GitHub.  Thanks for any help you can provide to harden the cc65 josystick driver on the Apple //.
