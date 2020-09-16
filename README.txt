Elizabeth Bauch - Section B
I used cplusplus.com to remind me of how to do some things with vectors, files, etc. and I also read piazza posts to
understand the assignment requirements. I love piazza!

Test 1 for input file explanation:
I test to see if each of the category id's are not between 1 and 4 inclusive in the load function.
I used chars to do this test like so:
else if ((category_id < '1') || (category_id > '4'))
which can be done because chars are technically integers so it tests if the category id is less than 31 or greater
 than 34 (according to the ASCII chart). If they are not between 1 and 4 inclusive, then it prints out:
"Input file \"filename\" appears to not be a proper file!" and returns false.

Test 2 for input file explanation:
This tests if the yes and no answers match up according to the 4 different categories (Introvert and Extrovert, Sensing
and Intuition, etc.)
This is done by testing if one of the answer choices is I, that the other answer choice is E, or vice versa. And I do the
same test for N and S, F and T, and P and J which is also done in the load function, but it also uses a function I
created called checkAnswer. checkAnswer works by using a switch statement so that if yes_answer is 'I', then return b=='E'.
This is so that even if the yes_answer is 'I', if the no_answer is not 'E', then it would still return false, because
that would mean at least one of the answers for the category was incorrect for the question. Each case in the switch statement
does the same for the other 3 categories. Then in the load function I use this else if statement:
else if (!checkAnswer(ans1, ans2) && !checkAnswer(ans2, ans1))
which says if both of these scenarios return false, then it is not a valid file, but if one returns true then it is.
That way the order of I or E being in the yes or no answer would not matter.
