#DO NOT search Google for 'Tentacles'#
##Exploring how to create snakes/tentacles##

Recently I have been exploring how to procedurally create tentacles and found that the problem in doing so stems from my original vision of 'medusa' like snakes flowing out of a central object, and created from two main parts: a snake-like look and a snake-like animation. Unfortunately, at this time, I have not been able to satisfactorily figure it out. Though I could sketch out relatively good looking tentacles and google images and videos of snakes and octopi projecting that motion into code became quite a different matter entirely.

##Snake-Like Look##
For the creation of tube-like structures I quickly came to find that I would require the use of an algorithm called PTR (Parallel Transport Frames). This is based on the concept of taking a line and separating it into segments where we could move a vector along its length that remains parallel to the line and which also helps retain the least amount of change from the last defined. In particular we do not want the normal axis flipping between segments or else we get a twisting effect that can be seen when using the older 'Frenet' frame approach during curve straightening. Fortunately Cinder already has a great implemention of creating PTR objects from 3D splines in their samples directory which can easily visualize the effects of the Frenet twisting as well as the PTR lack of twisting as seen below.

![Image of PTR created 3D Tube](../project_images/PTR_1.jpg?raw=true "Image of PTR created 3D Tube")
&nbsp;
![Image of Frenet created 3D Tube](../project_images/PTR_2.jpg?raw=true "Image of Frenet created 3D Tube")

The problems came from after I could create tube like objects that resembed snakes they still needed to be animated. Merely moving the points of the spline curves using sine and cosine diminishing curves was not working very well for myself, and did not leave itself easily open to participant disturbance. I then thought perhaps it would be best to have the points affected by an outward forcing vector field that I could easily manipulate using Optical flow.

##Vector Fields##
Iniially I had foolishly thought merely placing a vector field would fix my problems but it quickly became apparent that I would need some sort of constraints projected onto the points or else they would indefinitely move away from the center. There also needed to be some sort of constraints between each of the points within one 'snake' which naturally lead me to exploring Verlet physics which is an ideal way to create constraints between soft body objects - at least from my previous experiences with soft bodies using Bullet physics (and to a lesser extent Box2D which doesn't fully support them out ofteh 'box' just yet). This because Verlet is predominantly focused on the inertia of objects as opposed to more traditional Euler methods which focus on positions. This is of course based on my rough and basic interpretations.

I imagined a string of points connected by Verlet constraints that would flow outwards from a centre but unfortunately i found Bullet Physics a bit constraining as it doesn't seem to support localized gravity that would allow me to have many snakes all flowing in different directions without the major overhead of several Bullet 'worlds'. This and my curousity into trying to build my own lead me to play with ceating my own 'Verlet Rope' that I could use for this purpose. 

Unfortunately I ran into a huge number of memorory and reference pointing issues and thus also out of time before my first major milestone of showing something at an event on the 27th, so I had to simplify into static objects that I randomized for now which doesn't look too bad. I do still want to look into procedural creation and vertex-mode animation but as the project moves forward I am also concerned about about over complicating the piece without good reason. This is definitely something I will have to further explore. 

To be continued ...
