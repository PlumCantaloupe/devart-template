# A New Direction By Necessity

With the recent problems of creating moving tentacles I decided I must move onto a new or interim solution for the event on Thursday (tomorrow). As I was currently working on turning on my hobby deferred renderer project into a Cinder block (add-on for Cinder frameworks) this past weekend (so that it woudl be easier for myself and others to use in projects) I found myself instinctively and unknowingly playing with the concepts of a central object being surrounded bu other elements (such as lights) - see below.

![Image of Deferred Renderer Template](../project_images/DeferredRenderer_Test.jpg?raw=true "Image of Deferred Renderer Template")

Looking at this image it is evident that my mind is still on the concept of an individual focus in my other projects as well, so it felt natural to look towards this area as alternative method of creating the effect I wanted. Even more telling was a basic "game" I was proceeded to play with after creating the block that also built upon the same central sphere object but this time in a "low-poly" look as seen below.

![Image of Deferred Renderer Game](../project_images/DeferredRenderer_Game.jpg?raw=true "Image of Deferred Renderer Game")

I really enjoyed this low-poly look as it really made the visuals and deferred lighting and shadows pop. A low-poly geometric shape also suggests man-made and artificial to me which further adds to my concept of "man-mde/individual-made" constructs of self blinding/overshadowing the world around the us. Staring at this game for a few minites I decided, with only a few hours to implement before the night was done, this felt a good direction to head towards.

I also moved away from procedural creation and back into the core concept of tentacles or spikes moving out of an object. I created 3 "low-poly spikes" in Maya and exported as .objs I then loaded into Cinder to move into the scene at random positions, scales, and movement speeds. For the scene to become completely crowded I had to create 300 instances of these "spikes" and used Cinder's amazing timeline code to ease into and out of the scene. I imagine the spikes will start to peak out of the ground as a participant stands on a pedstal in front of the installation, and recede when that same participant steps off the pedastal. Following is a series of images representing the spike growth.

In the next post I will detail how the installation, even in its admittedly primitive form, was received at the event.

![Spike Growth 1](../project_images/DeferredRenderer_1.jpg?raw=true "Spike Growth 1")

![Spike Growth 2](../project_images/DeferredRenderer_2.jpg?raw=true "Spike Growth 2")

![Spike Growth 3](../project_images/DeferredRenderer_3.jpg?raw=true "Spike Growth 3")

![Spike Growth 4](../project_images/DeferredRenderer_4.jpg?raw=true "Spike Growth 4")
