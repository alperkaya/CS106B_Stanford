/*
 * CS 106B/X Patient Queue
 * This file contains the main program and user interface for testing your
 * various patient queues.
 *
 * Different instructors / courses / quarters give different versions of
 * this assignment, some giving only a single Patient Queue class to write,
 * others asking the students to write several kinds of queues, such as ones
 * implemented using a Vector, array, doubly-linked list, sorted list,
 * binary heap, binomial heap, skip list, etc.
 *
 * So this client program contains various ifdef statements to try to gracefully
 * handle all of the various kinds of queues that might or might not be present
 * in the assignment.  This logic relies on the #define statements in the various
 * *pq.h files to match the #ifdef statements in this file.
 *
 * You can modify this file if you like, to add other tests and so on.
 * But your turned-in files should work properly with an unmodified version of
 * all provided code files.
 *
 * @author Marty Stepp
 * @version 2017/10/31
 */

#include <algorithm>  // For sort, reverse
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "random.h"
#include "simpio.h"
#include "vector.h"

// include the various kinds of PQs for the assignment
#include "linkedpq.h"
#include "heappq.h"

static const bool RIG_RANDOM_NUMBERS = true;  // true to use same random sequence every time
static const int RANDOM_STRING_LENGTH = 6;    // max length of random strings in bulk en/deQ

// function prototype declarations
// (some are declared as templates so that they work with any type of queue)
static std::string randomString(int maxLength);
template <typename T> void test(T& queue);
template <typename T> void bulkDequeue(T& queue, int count);
template <typename T> void bulkEnqueue(T& queue, int count);
static void easterEgg();

int main() {
    std::cout << "CS 106B/X Hospital Patient Check-in System" << std::endl;
    std::cout << "==========================================" << std::endl;

    if (RIG_RANDOM_NUMBERS) {
        setRandomSeed(106);
    }

    std::string prompt = "Choose PQ type: ";
    std::string choice = "Q";
    int pqCount = 0;

#ifdef _vectorpq_h
    prompt += "V)ector, ";
    pqCount++;
    choice = "V";
#endif

#ifdef _arraypq_h
    prompt += "A)rray, ";
    pqCount++;
    choice = "A";
#endif

#ifdef _linkedpq_h
    prompt += "L)inked, ";
    pqCount++;
    choice = "L";
#endif

#ifdef _doublylinkedpq_h
    prompt += "D)oubly, ";
    pqCount++;
    choice = "D";
#endif

#ifdef _skiplistpq_h
    prompt += "S)kipList, ";
    pqCount++;
    choice = "S";
#endif

#ifdef _heappq_h
    prompt += "H)eap, ";
    pqCount++;
    choice = "H";
#endif

#ifdef _binomialpq_h
    prompt += "B)inomial, ";
    pqCount++;
    choice = "B";
#endif

#ifdef _extrapq_h
    prompt += "E)xtra, ";
    pqCount++;
    choice = "E";
#endif

    prompt += "Q)uit? ";

    while (true) {
        // (maybe) prompt for pq type
        if (pqCount > 1) {
            cout << endl;
            choice = toUpperCase(trim(getLine(prompt)));
        }
        if (choice.empty() || choice == "Q") {
            break;
#ifdef _vectorpq_h
        } else if (choice == "V") {
            VectorPQ pq;
            test(pq);
#endif

#ifdef _arraypq_h
        } else if (choice == "A") {
            ArrayPQ pq;
            test(pq);
#endif

#ifdef _linkedpq_h
        } else if (choice == "L") {
            LinkedPQ pq;
            test(pq);
#endif

#ifdef _doublylinkedpq_h
        } else if (choice == "D") {
            DoublyLinkedPQ pq;
            test(pq);
#endif

#ifdef _skiplistpq_h
        } else if (choice == "S") {
            SkipListPQ pq;
            test(pq);
#endif

#ifdef _heappq_h
        } else if (choice == "H") {
            HeapPQ pq;
            test(pq);
#endif

#ifdef _binomialpq_h
        } else if (choice == "B") {
            BinomialPQ pq;
            test(pq);
#endif

#ifdef _extrapq_h
        } else if (choice == "E") {
            ExtraPQ pq;
            test(pq);
#endif

        } else if (choice == "TNG") {
            easterEgg();
        }

        if (pqCount <= 1) {
            break;
        }
    }

    std::cout << std::endl;
    std::cout << "Exiting." << std::endl;
    return 0;
}

/*
 * Returns a randomly generated string of letters up to the given length.
 */
static std::string randomString(int maxLength) {
    int length = randomInteger(1, maxLength);
    std::ostringstream out;
    for (int i = 0; i < length; i++) {
        char ch = (char) ('a' + randomInteger(0, 25));
        out << ch;
    }
    return out.str();
}

/*
 * Prompts the user to perform tests on any type of queue.
 * Each method of the queue has a corresponding letter or symbol to type that
 * will call that method on the queue and display the results as appropriate.
 */
template <typename T>
void test(T& queue) {
    while (true) {
        std::cout << endl;
//        queue.debug();
        std::cout << "Current patient queue:" << std::endl;
        std::cout << queue;
        if (queue.isEmpty()) {
            std::cout << " (empty)" << std::endl;
        } else {
            std::cout << " (not empty)" << std::endl;
        }

        std::string prompt = "N)ew, F)ront, U)pgrade, P)rocess, B)ulk, C)lear, Q)uit?";
        std::string choice = toUpperCase(trim(getLine(prompt)));
        if (choice.empty() || choice == "Q") {
            break;
        } else if (choice == "U") {
            std::string value = getLine("Name? ");
            int oldPriority = getInteger("Old priority? ");
            int newPriority = getInteger("New priority? ");
            queue.upgradePatient(value, oldPriority, newPriority);
        } else if (choice == "C") {
            queue.clear();
        } else if (choice == "P") {
            std::string value = queue.processPatient();
            std::cout << "Processing patient: \"" << value << "\"" << std::endl;
        } else if (choice == "N") {
            std::string value = getLine("Name? ");
            int priority = getInteger("Priority? ");
            queue.newPatient(value, priority);
        } else if (choice == "F") {
            std::string name = queue.frontName();
            int pri = queue.frontPriority();
            std::cout << "Front of line is \"" << name << "\" with priority " << pri << std::endl;
        } else if (choice == "B") {
            int count = getInteger("How many patients? ");
            std::string choice2 = toUpperCase(trim(getLine("N)ew or P)rocess: ")));
            if (choice2 == "N") {
                bulkEnqueue(queue, count);
            } else if (choice2 == "P") {
                bulkDequeue(queue, count);
            }
        } else if (choice == "TNG") {
            easterEgg();
        }
    }
}

/*
 * Dequeues the given number of patients from the queue.
 * Helpful for bulk testing.
 */
template <typename T>
void bulkDequeue(T& queue, int count) {
    for (int i = 1; i <= count; i++) {
        std::string value = queue.processPatient();
        std::cout << "#" << i << ", processing patient: \"" << value << "\"" << std::endl;
    }
}

/*
 * Enqueues the given number of patients into the queue, either in random,
 * ascending, or descending order.
 * Helpful for bulk testing.
 */
template <typename T>
void bulkEnqueue(T& queue, int count) {
    std::string choice2 = trim(toUpperCase(getLine("R)andom, A)scending, D)escending? ")));
    if (choice2 == "R") {
        for (int i = 0; i < count; i++) {
            std::string value = randomString(5);
            int priority = randomInteger(1, count);
            queue.newPatient(value, priority);
            std::cout << "New patient \"" << value << "\" with priority " << priority << std::endl;
        }
    } else if (choice2 == "A" || choice2 == "D") {
        Vector<std::string> toAdd;
        for (int i = 0; i < count; i++) {
            toAdd.add(randomString(RANDOM_STRING_LENGTH));
        }
        if (choice2 == "A") {
            for (int i = 0; i < toAdd.size(); i++) {
                std::string value = toAdd[i];
                int priority = i + 1;
                queue.newPatient(value, priority);
                std::cout << "New patient \"" << value << "\" with priority " << priority << std::endl;
            }
        } else {
            for (int i = toAdd.size() - 1; i >= 0; i--) {
                std::string value = toAdd.get(i);
                int priority = i + 1;
                queue.newPatient(value, priority);
                std::cout << "New patient \"" << value << "\" with priority " << priority << std::endl;
            }
        }
    }
}

/*
 * This assignment is about a queue, so here is a silly hidden function that
 * prints some ASCII art and text about the character Q from the TV show,
 * "Star Trek: The Next Generation".
 *
 * Does it have very much to do with this assignment? No.
 * Did that stop me from adding it? NO.
 *
 * Total number of students who have ever mentioned to me that they found this: 6.
 *
 * If you haven't seen ST:TNG, well, I don't know what to tell you.  Go watch it.
 * Picard? Engaged.
 * Data? Intriguing.
 * Riker? Rikery.
 * Worf? Son of Mogh.
 * Wesley? Shut up Wesley!
 * Q? An irritable godlike pandimensional being? Money.
 * Troi? ... Well, you can't win 'em all.
 *
 * Text courtesy of: http://en.memory-alpha.org/wiki/Q
 * ASCII art courtesy of: http://www.chris.com/ascii/index.php?art=television/star%20trek
 */
static void easterEgg() {
    std::cout << "                                _____..---========+*+==========---.._____" << std::endl;
    std::cout << "   ______________________ __,-='=====____  =================== _____=====`=" << std::endl;
    std::cout << "  (._____________________I__) - _-=_/    `---------=+=--------'" << std::endl;
    std::cout << "      /      /__...---===='---+---_'" << std::endl;
    std::cout << "     '------'---.___ -  _ =   _.-'    *    *    *   *" << std::endl;
    std::cout << "                    `--------'" << std::endl;
    std::cout << endl;
    std::cout << "                 _____.-----._____" << std::endl;
    std::cout << "    ___----~~~~~~. ... ..... ... .~~~~~~----___" << std::endl;
    std::cout << " =================================================" << std::endl;
    std::cout << "    ~~~-----......._____________.......-----~~~" << std::endl;
    std::cout << "     (____)          \\   |   /          (____)" << std::endl;
    std::cout << "       ||           _/   |   \\_           ||" << std::endl;
    std::cout << "        \\\\_______--~  //~~~\\\\  ~--_______// " << std::endl;
    std::cout << "         `~~~~---__   \\\\___//   __---~~~~'     " << std::endl;
    std::cout << "                   ~~-_______-~~" << std::endl;
    std::cout << endl;
    std::cout << "                  xxxXRRRMMMMMMMMMMMMMMMxxx,." << std::endl;
    std::cout << "              xXXRRRRRXXXVVXVVXXXXXXXRRRRRMMMRx," << std::endl;
    std::cout << "            xXRRXRVVVVVVVVVVVVVVVXXXXXRXXRRRMMMMMRx." << std::endl;
    std::cout << "          xXRXXXVVVVVVVVVVVVVVVVXXXXVXXXXXXRRRRRMMMMMxx." << std::endl;
    std::cout << "        xXRRXXVVVVVttVtVVVVVVVVVtVXVVVVXXXXXRRRRRRRMMMMMXx" << std::endl;
    std::cout << "      xXXRXXVVVVVtVttttttVtttttttttVXXXVXXXRXXRRRRRRRMMMMMMXx" << std::endl;
    std::cout << "     XRXRXVXXVVVVttVtttVttVttttttVVVVXXXXXXXXXRRRRRRRMMMMMMMMVx" << std::endl;
    std::cout << "    XRXXRXVXXVVVVtVtttttVtttttittVVVXXVXVXXXRXRRRRRMRRMMMMMMMMMX," << std::endl;
    std::cout << "   XRRRMRXRXXXVVVXVVtttittttttttttVVVVXXVXXXXXXRRRRRMRMMMMMMMMMMM," << std::endl;
    std::cout << "   XXXRRRRRXXXXXXVVtttttttttttttttttVtVXVXXXXXXXRRRRRMMMMMMMMMMMMM," << std::endl;
    std::cout << "   XXXXRXRXRXXVXXVtVtVVttttttttttttVtttVXXXXXXXRRRRRMMMMMMMMMMMMMMMR" << std::endl;
    std::cout << "   VVXXXVRVVXVVXVVVtttititiitttttttttttVVXXXXXXRRRRRMRMMMMMMMMMMMMMMV" << std::endl;
    std::cout << "   VttVVVXRXVVXtVVVtttii|iiiiiiittttttttitXXXRRRRRRRRRRMMMMMMMMMMMMMM" << std::endl;
    std::cout << "   tiRVVXRVXVVVVVit|ii||iii|||||iiiiiitiitXXXXXXXXRRRRRRMMMMMMMMMMMMM" << std::endl;
    std::cout << "    +iVtXVttiiii|ii|+i+|||||i||||||||itiiitVXXVXXXRRRRRRRRMMMMMMRMMMX" << std::endl;
    std::cout << "    `+itV|++|tttt|i|+||=+i|i|iiii|iiiiiiiitiVtti+++++|itttRRRRRMVXVit" << std::endl;
    std::cout << "     +iXV+iVt+,tVit|+=i|||||iiiiitiiiiiiii|+||itttti+=++|+iVXVRV:,|t" << std::endl;
    std::cout << "     +iXtiXRXXi+Vt|i||+|++itititttttttti|iiiiitVt:.:+++|+++iXRMMXXMR" << std::endl;
    std::cout << "     :iRtiXtiV||iVVt||||++ttittttttttttttttXXVXXRXRXXXtittt|iXRMMXRM" << std::endl;
    std::cout << "      :|t|iVtXV+=+Xtti+|++itiiititittttVttXXXXXXXRRRXVtVVtttttRRMMMM|" << std::endl;
    std::cout << "        +iiiitttt||i+++||+++|iiiiiiiiitVVVXXRXXXRRRRMXVVVVttVVVXRMMMV" << std::endl;
    std::cout << "         :itti|iVttt|+|++|++|||iiiiiiiittVVXRRRMMMMMMRVtitittiVXRRMMMV" << std::endl;
    std::cout << "           `i|iitVtXt+=||++++|++++|||+++iiiVVXVRXRRRV+=|tttttttiRRRMMM|" << std::endl;
    std::cout << "             i+++|+==++++++++++++++|||||||||itVVVViitt|+,,+,,=,+|itVX'" << std::endl;
    std::cout << "              |+++++.,||+|++++=+++++++|+|||||iitt||i||ii||||||itXt|" << std::endl;
    std::cout << "              t||+++,.=i+|+||+++++++++++++|i|ittiiii|iiitttttXVXRX|" << std::endl;
    std::cout << "              :||+++++.+++++++++|++|++++++|||iii||+:,:.-+:+|iViVXV" << std::endl;
    std::cout << "              iii||+++=.,+=,=,==++++++++++|||itttt|itiittXRXXXitV'" << std::endl;
    std::cout << "             ;tttii||++,.,,,.,,,,,=++++++++++|iittti|iiiiVXXXXXXV" << std::endl;
    std::cout << "            tVtttiii||++++=,,.  . ,,,=+++++++|itiiiiiii||||itttVt" << std::endl;
    std::cout << "           tVVttiiiii||||++++==,. ..,.,+++=++iiiiiitttttVVXXRRXXV" << std::endl;
    std::cout << "        ..ttVVttitttii||i|||||+|+=,.    .,,,,==+iittVVVXRRMXRRRV" << std::endl;
    std::cout << "...'''ittitttttitVttttiiiiii|ii|++++=+=..... ,.,,||+itiVVXXVXV" << std::endl;
    std::cout << "      ,|iitiiitttttttiiiii||ii||||||||+++++,.i|itVt+,,=,==........." << std::endl;
    std::cout << "        ,|itiiiVtVtiii||iiiiii|||||||++||||tt|VXXRX|  ....  ..     ' ' '." << std::endl;
    std::cout << "          ,,i|ii||i||+|i|i|iiiiiiii||||ittRVVXRXRMX+, .  ...   .         ," << std::endl;
    std::cout << "    .       .,+|++|||||ii|i|iiiitttVVttXVVXVXRRRRXt+. .....  . .       ,. ." << std::endl;
    std::cout << "  . .          ,,++|||||||i|iiitVVVXXXXVXXVXXRRRV+=,.....  ....  ..       .." << std::endl;
    std::cout << "                  .,,++|||i|iittXXXXRMViRXXXXRVt+=, ..    ...... .        .." << std::endl;
    std::cout << "                   ,XX+.=+++iitVVXXXRXVtXXVRRV++=,..... .,, .              ." << std::endl;
    std::cout << "            ....       +XX+|i,,||tXRRRXVXti|+++,,. .,,. . . .. .      . ...." << std::endl;
    std::cout << "  . .          .      ..  ..........++,,..,...,.... ..             .. ..." << std::endl;
    std::cout << endl;
    std::cout << "Q was a highly powerful entity from a race of omnipotent, godlike "
              << "beings also known as the Q. Q appeared to the crews of several "
              << "Starfleet vessels and outposts during the 2360s and 2370s. "
              << "All command level officers in Starfleet are briefed on his "
              << "existence. One such briefing was attended by Benjamin Sisko "
              << "in 2367. He typically appears as a Humanoid male (though "
              << "he can take on other forms if he wishes), almost "
              << "always dressed in the uniform of a Starfleet captain." << std::endl;
    std::cout << "In every appearance, he demonstrated superior capabilities, but "
              << "also a mindset that seemed quite unlike what Federation scientists "
              << "expected for such a powerful being. He has been described, in "
              << "turn, as 'obnoxious,' 'interfering,' and a 'pest'. However, "
              << "underneath his acerbic attitude, there seemed to be a hidden "
              << "agenda to Q's visits that often had the best interests of "
              << "Humanity at their core." << std::endl;
    std::cout << std::endl;
    std::cout << "\"Worf... Eat any good books lately?\" -- Q" << std::endl;
}
