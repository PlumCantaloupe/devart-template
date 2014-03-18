# Moving to a Much Larger Pedestal

Over the last couple of weeks I have been constantly thinking on how best to utilize the original vision of a "mirror" that reflects the world around us. In my previous project post "Rethinking the Purpose" (just waiting to hear back why it isn't showing up on my dev art page) I spoke about how I wanted this piece no longer to be about the individual but rather many individuals as the piece tries to encourage collaborative thought and activism about the world around us. In this sense my original prototype, which included a small pedestal (project post "First Public Prototype Test"), for one individual didn't sit very well with me for both interactional and conceptual reasons. Lately I have been experimenting with OpenCV and crowd-computer interactions to better realize the vision of detecting many. I'll detail my explorations here.

## Crowd-Computer Interaction

There isn't a great deal of literature on how to build a versatile crowd-computer interaction platform. There are some examples that include looking for large changes in movement, for example all hands down or up, left, or right[1]; but when thinking about the crowd movement and shape itself there is some room yet for new exploration. My ideal system would involve a layer that detects the density of a crowd, localized movements of the "groups" and a rough estimate of their positions. I think this could work well for large crow movements but also for smaller numbers of groups that may be found interacting with this installation. Since, this is for gross group movements the detection methods need not be precise, but must account for various head positions (not just front on), and many occlusions. It is my hope that the final result may be something useful for not this installation but also larger installations as say a concert or event for example.

### Step 1 - Train the LBP Cascade

As many of the "face-detection" cascades floating around the internet for OpenCV require front-facing persons to detect a "head" they were not that useful for my purposes where I wanted to be able to detect not only people facing the installation but also moving away or beside it facing in multiple directions. I think there is a possibility of assuming only those facing your installation are interacting but I really want a versatile detection method for counting all people in front ofthe installation with some context as to their interest and direction, and besides, it was an excuse to learn how to train my own cascade.

In the end it took many tries, and few hours to go through images and manually cut out 3500 positive samples and 8000 negative sample (created a small convenience program to do this); and using the LBP training method as opposed to the HAAR method with a 4-core machine the training itself only took about 10 minutes which allowed for a great deal of trial and error in determining which settings would work best. I kept my max false alarm very low to allow for greater number of detections at the expense of more false positives. I figure since this is not a precision based interaction I would rather more detections than less and generalize the results later for more finite quantification.

Note: All positives focused on the head and neck (from most angles) as within crowds these are likely to to be the only visible areas of people.

![Image of LBP Training](../project_images/OpenCV_LBP_Training.jpg?raw=true "Image of LBP Training")
__Figure 1 - Screenshot of the settings IO used to train my LBP cascade.__

### Step 2 - Test the Cascade

While training the cascade I also created a small sample app that goes through various images to get an idea of how it worked. It did seem to work well but does have a great number of false positives, especially away from where people are located. To try and curb this number I also added a background subtraction step that allows me to ignore any "detections" outside of any new elements within the scene, which I assume are people moving into the frame. I still have false positive within a person silhouette, such as a shoulder or bag, but generally these detections will now be where people are.

![Image of Head Detections](../project_images/OpenCV_HeadDetections.jpg?raw=true "Image of Head Detections")
__Figure 2 - An image of the rough "head" detections I get with the LBP cascade.__

### Step 3 - Try to create a Density Generalization from the Results

After detecting the rough number of "heads" I need to smooth these results into some sort of density map. My initial attempt involves breaking the image into cells which I then use to count the number of "detections" within each cell giving each cell a colour to represent the number of detections (blue being none and moving towards red and the number increases). This seems to work well enough but it is too precise and I will be considering using smoothing algorithms to smooth the results (and false detections) into something less precise but more useful. I also need to play with the number of cells.

![Image of Cell Counting Approximation](../project_images/OpenCV_CellCounting.jpg?raw=true "Image of Cell Counting Approximation")
__Figure 3 - An image of the cell method of trying to smooth results into a desnity map.__

### Step 4 - Try and Capture Movement

I have yet to do this step but I really want to be able to capture the motion of a crowd so that can detect how "energetic" it is as it seems a useful variable to have, especially if it can give me the gross movements of different groups. I envision using optical flow for this but have yet to implement it and I also want to use motion as an indication of a person to further reduce the number of false positives. I am envisioning ignoring detections that are not consistently visible, and also those that do not move as another method of ignoring background detections and remove the tricky background subtraction step where lighting changes, camera changes, or lack of an empty background image can present many difficulties for live installations.

### Other Possible Methods

As I have been exploring OpenCV for a while I had missed some other detection methods that may return better results. Some of these include using SVM detections and HOGdescriptors [2][3] as they apparently are better able to capture people through image gradient changes. Some preliminary tests show that the defaultPeopleDetector is not that great for occlusions as it is looking for complete bodies and I am not sure I have time to learn how to train my own detector. It is something I would like to explore later though.

Also, much of the academic research of crowd-detections centres around surveillance and using much more complex and accurate counting methods by utilizing different algorithms that smooth out the density and false positives [4]; but I must admit these are a bit over my head at this time though I would like to revisit.

## And Now What

I will do another post in a couple of days with some mockups of the new installation prototype. Though it will retain the same basic layout the size of the pedestal should now accommodate a few more people, without an Arduino component, and the interaction will be a different and more continuous - one of Snibbe's “best practises for multi-user exhibits” [5] ).

### References

1. Maynes-Aminzade, D., Pausch, R., & Seitz, S. (2002, October). Techniques for interactive audience participation. In Proceedings of the 4th IEEE International Conference on Multimodal Interfaces (p. 15). IEEE Computer Society.
2. 2. Dalal, N., & Triggs, B. (2005, June). Histograms of oriented gradients for human detection. In Computer Vision and Pattern Recognition, 2005. CVPR 2005. IEEE Computer Society Conference on (Vol. 1, pp. 886-893). IEEE.
3. http://docs.opencv.org/modules/gpu/doc/object_detection.html
4. Rodriguez, M., Laptev, I., Sivic, J., & Audibert, J. Y. (2011, November). Density-aware person detection and tracking in crowds. In Computer Vision (ICCV), 2011 IEEE International Conference on (pp. 2423-2430). IEEE.
5. Snibbe, S. S., & Raffle, H. S. (2009, April). Social immersive media: pursuing best practices for multi-user interactive camera/projector exhibits. InProceedings of the SIGCHI Conference on Human Factors in Computing Systems (pp. 1447-1456). ACM.
