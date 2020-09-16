1. Elizabeth Bauch - Section B
I used Piazza, cplusplus.com, and the textbook to help me with this assignment to understand how stacks and queues work.

2. Challenges:
Some challenges I encountered was understanding the difference between a stack and a queue. At first, I thought that
using a queue meant I would be solving the maze backwards, and then I realized that it could start from the same place,
but that it evaluates the points differently. Meaning, for the queue it evaluates the points immediately, and finds
valid points next to the current point and adds them on to the queue, so it goes back and forth between different possible
paths because it adds right, up, down, left (in my code) immediately. Versus, in the stack, if it finds a path that works,
going up for example, it keeps going in that direction, and then once it can't keep going (like in 8-example.txt), then
it will go back to the right direction because that point was added earlier in the stack and keep going from there.
(I'm sorry if this explanation is a bit confusing, but I want to be able to refer to it later)
Another challenge I encountered is that I figured out how to use a stack, and then when I went to use a queue I realized
adding some other functions like _nextPoint and _pushPoint would be useful. This was because depending on whether I
was using a stack or a queue the next point would be the top of the stack or the front of the queue, and I would
either be pushing a point onto the stack or the queue.

3. Likes/Dislikes:
I liked this assignment because it was a very visual assignment with the mazes which I think was useful for learning
how stacks and queues can be used. I also liked this problem was pretty complex but not too complex, and so it was
somewhat difficult to logically think through in order to write the code, but it was a good experience seeing a problem
that is a lot easier to deal with by writing a program that solves it for you!
I disliked that some of the instructions were a bit vague. For example, I realized
that for the 8-example.txt file if I evaluate the up point first and then the right point, it causes my @ signs to
move in the same direction as the example for the assignment. Does it matter if the @ signs move in the same direction
(evaluates the points in the same order), or does it only matter that it reaches the goal? Maybe some specifications
about this would be useful.

4. I spent about 20 hours working on this assignment.