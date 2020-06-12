joytest
=======

This is a joystick test program for the cc65 joystick driver.  A problem was found with the original cc65 driver so it has being re-written by Oliver Schmidt.  I am creating this program to provide feedback on the new implementation when run on a variety of HW.  I have access to an Apple //e and an Apple //gs, each with a CH brand joystick attached.  By making this program available, I am hoping to get feedback from more of the community and get coverage of other HW.  Please download the disk image to assist in getting greater coverage of this new joystick driver:

[Download a disk image](https://github.com/jeremysrand/joytest/releases/download/0.4/joytest.dsk)

When run, the left side of the screen shows the current state of the joystick as read by the cc65 driver.  The direction of the joystick (if any) and the state of the two buttons is displayed.  The right side displays information about X or Y axis testing which may be useful for tweaking the thresholds used to determine direction.  Below that is a current X and Y position (0-255) as read by the ROM routine, not the cc65 driver.  If your joystick is not centred, producing noisy samples or some other problem outside of those with the cc65 driver itself, you may see that here.

If you have an accelerator, you may want to disable it.  For systems that shipped running at greater than 1MHz (like the //gs and the //c+), testing at 1MHz and at accelerated speed is useful.  Feel free to provide feedback about the behaviour of the driver on a machine with an optional accelerator card active.  Although this information is interesting, but I don't think the cc65 project intends to add any support for accelerator detection and handling.  Most important is to show that it works acceptably at the speed(s) supported by the platform as it originally shipped.

There are a series of tests that are worth running.

Basic Operation:
--------------------

For this test, ignore the right hand side the of screen and focus on the left side.  Just manipulate the joystick and ensure that the motion of the joystick is reflected on the screen.  Press each button and make sure that the appropriate button number highlights.  Make slow and deliberate movements as well as fast movements with the joystick and ensure that the changes on the screen reflect those motions.

X Axis Test:
--------------

In this test, we will be checking the thresholds on the X axis for declaring the joystick to be pushed to the left, to the right or in the centre.  First, press the X key to ensure you are in X axis testing mode.  Then press C to clear any numbers that might have been there from previous testing.  The way this test works is that when the program detects that the cc65 driver has changed the position of the joystick on the X axis, the ROM routine for reading the X axis position is called.  Because there is a short delay between the sample taken by the cc65 driver and by the read done by the ROM routine, slow movements of the joystick in the X direction are key in this test.  If you move the joystick quickly, the value retrieved by the ROM routine will have little bearing on the actual value that triggered the position change in the cc65 driver.  If you need to clear the stats, press C at any time to try again.

Start with the joystick in the centre and slowly push the joystick to the right.  At some point, you should notice a value for the "lowest right" is filled in.  This is the value read by the ROM routine from just after when the cc65 driver changed from centre to right position.  Continue pushing to the extreme right and then slowly return to the centre.  When the driver changes from right position to centre again, the "highest centre" value will fill in.  Move slowly to the right again and try to stop just at the point when the position changes from centre to right.  Check to see if this is a reasonable position on your joystick.  Is it far enough from the centre and not too close to the extreme right edge?  You may need to trim your joystick if it has trim controls.  After doing this for a bit, what are the values you got for highest centre and lowest right.  Try doing the above with the joystick pressed up, moving from up to upper right and then back to up position.  And again with the joystick down, moving to the right and back to centre.  Any change in these two threshold values read?  On my HW, I get 222 for both highest centre and lowest right.

Do the same again except this time move from the centre to the left and then back to the centre.  This time, the values for highest left and lowest centre will get filled in.  On my HW, I get 13 for both of these values.  Note that I have a difficult time getting anything for highest left and it stays "n/a" for quite some time.  That means that it read 0 from the ROM routine just after the direction changed from centre to left, even though my joystick is not entirely all the way to the left.  If I try many times, I can get as high as 13 for highest left.  I suspect my joysticks drop from about 13 to 0 with not much resolution in that range for some reason.  Be sure to try motions to the left with the joystick also pressed all the way up and down.

Y Axis Test:
--------------

This is essentially a repeat of the tests described for the X axis except this time we will slowly be pushing the joystick up and then down and measuring the thresholds in that direction.  Press Y to do a Y axis test and C to clear any thresholds you may have gotten from previous tests.  Then, redo the same kinds of motions you performed on the X axis except for up and down.

With my HW, I get 14 for the highest up and lowest centre thresholds and 223 for the highest centre and lowest down thresholds.

Second Joystick:
--------------------

If you have a second joystick, it can be tested also.  Press 2 to switch to the second joystick (1 returns you to the first joystick).  Then repeat all of the tests described above except with this joystick.

Issues Or Feedback:
------------------------

If you encounter any oddities or your thresholds from the X axis or Y axis tests are weird, please contact me or raise an issue against this project on GitHub.  Thanks for any help you can provide to harden the cc65 josystick driver on the Apple //.
