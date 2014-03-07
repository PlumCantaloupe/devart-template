#A New Direction#
##By Necessity##

With the recent problems of creating moving tentacles I decided I must move onto a new or interim solution for the event on Thursday (tomorrow). As I was currently working on turning on my hobby deferred renderer project into a Cinder block (add-on for Cinder frameworks) I found myself instinctively playing with the concepts of a central object being surrounded bu other elements (such as lights) - see below.

![Image of Deferred Renderer Template](../project_images/DeferredRenderer_Test.jpg?raw=true "Image of Deferred Renderer Template")

Looking at this image it is evident that my mind is still on the concept of an individual focus in my other projects as well, so it felt natural to look towards this area as alternative method of creatingthe effect I wanted. Even more telling was a basic "game" I was playing with that built upon the same central sphere object but this time in a "low-poly" look as seen below.

![Image of Deferred Renderer Game](../project_images/DeferredRenderer_Game.jpg?raw=true "Image of Deferred Renderer Game")

I really enjoyed this low-poly look as it really made the visuals and deferred lighting and shadows pop, as well a low-poly geometric shape suggesting man-made which further adds to my concept of a "man-mde/individual-made" constructs of self blinding/overshadowing the world around the self. Staring at this game for a few minites I decided, with only a few hours to implement before the night was done for me, that this was a good direction to go.

I moved away from procedural creation and back into the var concept of tentacles or spikes moving out of an object. I created 3 "low-poly spikes" in Maya and exported as .objs I would then load into Cinder and move into the scene at random positions, scales, and movement speeds. For the scene to become completely crowded I had to create 300 nstances of these "spikes" and used Cinder's amazing timeline code to ease into and out of the scene. I imagine teh spikes will start to peak out of the ground as a participant stands on a pedstal in front of the installation, and recede when that same participant steps off the pedastal. Following is a series of images representing the spike growth.

![Spike Growth 1](../project_images/DeferredRenderer_1.jpg?raw=true "Spike Growth 1")

![Spike Growth 2](../project_images/DeferredRenderer_2.jpg?raw=true "Spike Growth 2")

![Spike Growth 3](../project_images/DeferredRenderer_3.jpg?raw=true "Spike Growth 3")

![Spike Growth 4](../project_images/DeferredRenderer_4.jpg?raw=true "Spike Growth 4")