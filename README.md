# CS-UY 4783 Project 1
Cryptanalysis of L-Symbol Challenge for CS-UY 4783

## Assignment

**Grading and Submission Policies**: Project 1 will contribute to the class grade as specified in the syllabus. All students must submit for Project 1 using the appropriate link in the Tests & Quizzes content area, and using the submission naming convention specified below. If you want just one group member to submit your long submission, the other team members have to submit some text or file with a pointer to the submitting student in their team.

The project should be realized by a team of 2, 3 or 4 students (only well motivated exceptions will be considered acceptable). The implementation can be in any programming language, but those choosing C or C++ will receive a small extra credit, as these are the most recommended (for combined performance and user convenience) programming languages to implement cryptography solutions in the real world. The project comes with a minimal assignment and requires a submission of both software and a report being graded mainly by the TA according to scoring criteria defined below; any additional work you perform will be considered extra credit work (specifically, Extra Credit 3) if later also submitted under the appropriate space for Extra Credit 3 under Tests and Quizzes. Teams are supposed to split the amount of work more or less equally among the team members; if a team splits the work in a way that is too unbalanced, details should be mentioned to the instructor and the score given to team members may be suitably unbalanced.

**Project 1 (Cryptanalysis of a class of ciphers):**

This cryptanalysis project consists of a software implementation of an algorithm that tries to decrypt an L-symbol challenge ciphertext computed using a specific cipher. Informally speaking, your program's goal is to find the plaintext used to compute this ciphertext within a reasonable amount of time. Specifically, your program should print on screen something like "Enter the ciphertext:", obtain the ciphertext from stdin, apply some cryptanalysis strategy and output on screen something like "My plaintext guess is:" followed by the plaintext found by your strategy. In doing that, your program is allowed access to:

The ciphertext (to be taken as input from stdin)
A plaintext dictionary (to be posted on top of this web page), containing a number q of plaintexts, each one obtained as a sequence of space-separated words from the English dictionary
Partial knowledge of the encryption algorithm used (to be described below).
Your program is not allowed access to:

The key used by the cipher.
Part of the encryption scheme (to be detailed below).
The plaintext is a space-separated sequence of words from the English dictionary; thus, each symbol is either a space or one of the 26 lower-case letters from the English alphabet and cannot be a special character, punctuation symbol or upper-case letter; the sentence may not be meaningful, for sake of simplicity.

The key is a sequence of t numbers between 0 and 26.  

The ciphertext looks like a sequence of symbols from {\<space\>,a,..,z}.

A text file Dictionary1 containing a number u of L-symbol candidate plaintexts will be provided to you (as an attachment at the top of this page), and you should feel free to use its content as part of your code.

A text file Dictionary2 containing a number v of English words will be provided to you (as an attachment at the top of this page), and you should feel free to use its content as part of your code.

Your program will be run using different parameters (e.g., L=500, u=5, v=50, and t between 1 and 24), and on a number of challenge ciphertexts, each computed using a potentially different variant of the encryption scheme.

Your program should return as output a guess for which L-symbol plaintext was encrypted.

Each ciphertext will be computed from a plaintext selected in one of the following two ways:

randomly and independently choosing one of the L-symbol plaintexts in Dictionary1 or
concatenating words randomly and independently chosen from Dictionary2 (any two words being separated by a space, until one has an L-symbol plaintext).
All the encryption schemes used have the following common features:

The message space and ciphertext space are the set {\<space\>,a,..,z}^L. In other words the message m can be written as m[1],...,m[L], where each m[i] is in {\<space\>,a,..,z}, and the ciphertext c can be written as c[1],...,c[L], where each c[i] is in {\<space\>,a,..,z}
The key space is the set {0,..,26}^t. In other words the key k can be written as k[1],...,k[t], where each k[j] is in {0,..,26}, for j=1,..,t.
The encryption algorithm computes each c[i] as the (lexicographic) shift of m[i] by k[j(i)] positions, where the computation of each j(i) is left unspecified and may depend on i,t,L. In other words, each ciphertext symbol c[i] is the shift of the plaintext symbol m[i] by a number of position equal to one of the key symbols, which symbol being chosen according to an undisclosed, deterministic, and not key-based, scheduling algorithm that is a function of i, t and L.
Your program will be scored based on two tests.

In the first test, your program will be run many times, each time on a new ciphertext, computed using the above encryption scheme and a plaintext randomly chosen from the plaintext Dictionary 1, each time with a different scheduling algorithm. On the first execution, the scheduling algorithm will compute “j(i) = 1+ i mod t”. On the other executions, the scheduling algorithms will be more and more complex variations of this one. In this test we will likely choose L=500, and a plaintext dictionary with u=5 plaintexts.

In the second test, your program will be run a few times, each time on a new ciphertext, computed using a plaintext obtained as a space-separate sequence of words that are randomly chosen from a subset of the set of all English words (specifically, a few words randomly taken from Dictionary 2) and the above encryption scheme, with a different scheduling algorithm. In this test we will likely choose L=500 and v=50 words.

Your executable file should be named "\<last name1\>-\<last name2\>-\<last name3\>-decrypt". Upon execution, it should obtain the ciphertext from stdin, and finally return the output plaintext on stdout within x minutes (or else it will be declared to default to an incorrect guess); most likely, we will choose x = 1 on test 1 and x = 3 on test 2.

If you want to propose more than one cryptanalysis approach, you need to clarify that in your report, and each of your approaches will be tested. You cannot pick more than one approach per team member. Your overall team score will be an average across the success of the various approaches.

Your accompanying **report** should at least include the following sections:

 1. title of your project (based on your approach); something like "Cryptanalysis of a class of ciphers based on (...)"; the symbol (...) should be replaced with an expression summarizing the main idea(s) in your approach

 2. an introduction containing the team member names; the list of project tasks performed by each student in the team; the number of cryptanalysis approaches you are submitting; and any modifications you made with respect to the above specifications

 3. a detailed informal explanation (using much more English than pseudo-code) of the cryptanalysis approach or approaches used in your program

 4. a detailed rigorous description (using much more pseudo-code than English) of the cryptanalysis approach or approaches used in your program

Allowed extensions (to be considered as **extra credit**) include any one among the following:

a report section containing a brief (i.e., <= 2 pages) survey on substitution or permutation ciphers
a report section containing a brief (i.e., <= 2 pages) survey on cryptanalysis approaches for substitution or permutation ciphers
(top extra credit:) if you think your cryptanalysis strategy works well (meaning, it quickly finds the plaintext from the ciphertext) for test2 and the given Dictionary 2, try increasing the number of words in this file and see if your strategy still works well; at which number (of words in this file) do you note a large increase in your strategy's running time?
Your submission should be a zip file containing at least the following files: project report (in pdf form), source and executable. Please name your zip file as\<last-name1\>\<last-name2\>\<last-name3\>-cs6903s19project1 and your contained files as \<last-name1\>\<last-name2\>\<last-name3\>-report, \<last-name1\>\<last-name2\>\<last-name3\>-source, \<last-name1\>\<last-name2\>\<last-name3\>-decrypt. Your submission will be judged based on the following **grading criteria**:

software correctness and usability (i.e., if you followed all of the above instructions, if software runs correctly, and is easy to use)
quality of report (i.e., how well written is your report)
cryptanalysis success (i.e., how many challenge ciphertexts your program successfully decrypted). If there are two or more submissions successfully decrypting the same number of challenge ciphertexts, we may rank them based on their (faster to slower) running time taken to produce their outputs.
A good cryptanalysis strategy not guessing any plaintext or an uninteresting cryptanalysis strategy guessing all plaintexts in the first test will be rewarded with a score around the B or B+ level. A good cryptanalysis strategy guessing all plaintexts in the first test will be rewarded with a score around the A- level. Mild success in the second test should be enough for a score in the A level.

The top team(s) will be rewarded with a bonus score directly on the class grade.

**Due date** is on the syllabus. No late submissions can be accepted without score penalty and early submissions are encouraged. You are strongly recommended to submit any questions to the TAs (see Syllabus content area for their contact info) and the instructor.
