/*PDF Library Used << Haru Free PDF Library 2.0.0 >>*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <bits/stdc++.h>
using namespace std;

#include "hpdf.h"
jmp_buf env;

#ifdef HPDF_DLL
void __stdcall
#else
void
#endif
    error_handler(HPDF_STATUS error_no,
                  HPDF_STATUS detail_no,
                  void *user_data)
{
    printf("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
           (HPDF_UINT)detail_no);
    longjmp(env, 1);
}

const char *font_list[] = {
    "Courier",
    "Courier-Bold",
    "Courier-Oblique",
    "Courier-BoldOblique",
    "Helvetica",
    "Helvetica-Bold",
    "Helvetica-Oblique",
    "Helvetica-BoldOblique",
    "Times-Roman",
    "Times-Bold",
    "Times-Italic",
    "Times-BoldItalic",
    "Symbol",
    "ZapfDingbats",
    NULL};

class QuestionPaper
{
public:
    int noOfEasy = 0, noOfHard = 0, noOfMedium = 0, totalEasy = 0, totalMed = 0, totalHard = 0;
    int totalQuestions = 0;
    vector<string> easy, medium, hard;
    vector<int> shuffEasy, shuffMed, shuffHard, que;

public:
    QuestionPaper(int easy, int medium, int hard)
    {
        this->noOfEasy = easy;
        this->noOfMedium = medium;
        this->noOfHard = hard;
        this->totalQuestions = easy + medium + hard;
        this->que.resize(totalQuestions);
    }

    void readFile(vector<string> &que, string s)
    {
        string temp = "";
        string path = "questions/" + s + ".txt";
        ifstream myfile(path);
        if (myfile.is_open())
        {
            char mychar;
            while (myfile)
            {
                mychar = myfile.get();
                if (mychar == '\n')
                {
                    que.push_back(temp);
                    temp.clear();
                }
                else
                    temp += mychar;
            }
        }
    }

    void createPaper()
    {
        if (noOfEasy)
            readFile(easy, "EASY");
        if (noOfMedium)
            readFile(medium, "MEDIUM");
        if (noOfHard)
            readFile(hard, "HARD");

        this->totalEasy = easy.size();
        this->totalMed = medium.size();
        this->totalHard = hard.size();

        shuffEasy.resize(totalEasy);
        shuffMed.resize(totalMed);
        shuffHard.resize(totalHard);

        for (int i = 0; i < max({totalEasy, totalHard, totalMed}); i++)
        {
            if (i < totalEasy)
                shuffEasy[i] = i;
            if (i < totalMed)
                shuffMed[i] = i;
            if (i < totalHard)
                shuffHard[i] = i;
        }

        random_device e1, e2, e3; // seeding
        mt19937 g1(e1()), g2(e2()), g3(e3());
        // shuffling index for question to make random selection among multiple paper distributive
        shuffle(shuffEasy.begin(), shuffEasy.end(), g1);
        shuffle(shuffMed.begin(), shuffMed.end(), g2);
        shuffle(shuffHard.begin(), shuffHard.end(), g3);

        // storing the needed quantity of questions in a vector
        for (int j = 0; j < max({noOfEasy, noOfMedium, noOfHard}); j++)
        {
            if (j < noOfEasy)
                que[j] = shuffEasy[j];
            if (j < noOfMedium)
                que[noOfEasy + j] = shuffMed[j];
            if (j < noOfHard)
                que[noOfEasy + noOfMedium + j] = shuffHard[j];
        }
    }
};

int main(int argc, char **argv)
{
    int noOfEasy = 0, noOfMedium = 0, noOfHard = 0, time = 0;
    int easyMarks = 0, mediumMarks = 0, hardMarks = 0, totalMarks = 0;
    cout << "----------------Welcome to DS Paper Generator--------------" << endl;
    cout << endl;
    cout << "Please Fill Up the necessary details so we can generated Required Paper Set for you" << endl;
    cout << endl;
    while (true)
    {

        while (true)
        {
            printf("Enter the number of Easy questions & marks for a easy question: ");
            cin >> noOfEasy >> easyMarks;
            if (noOfEasy > 25)
            {
                printf("Please enter number of question from 0 to 25\n");
            }
            else
            {
                totalMarks += easyMarks * noOfEasy;
                break;
            }
        }
        while (true)
        {
            printf("Enter the number of Medium questions: ");
            cin >> noOfMedium >> mediumMarks;
            if (noOfMedium > 25)
            {
                printf("Please enter number of question from 0 to 25\n");
            }
            else
            {
                totalMarks += mediumMarks * noOfMedium;
                break;
            }
        }
        while (true)
        {
            printf("Enter the number of Hard questions: ");
            cin >> noOfHard >> hardMarks;
            if (noOfHard > 25)
            {
                printf("Please enter number of question from 0 to 25\n");
            }
            else
            {
                totalMarks += hardMarks * noOfHard;
                break;
            }
        }

        if (noOfEasy + noOfMedium + noOfHard > 40)
        {
            printf("Total no of questions should be less than 40\n");
        }
        else
            break;
    }

    printf("Enter the total time (hours) alloted to exam: ");
    cin >> time;

    const char *Line1 = "Nirma University";
    const char *Line2 = "Institute Of Techology";
    const char *Line3 = "B. Tech in Computer Science and Engineering, Semester-III";
    const char *Line4 = "2CS301 Data Structures";
    const char *Line5 = "Roll/Exam no. :-__________                                                         Supervisor's initial: __________";
    string outline = "Time: " + to_string(time) + " Hours                                                                                 Max. Marks: " + to_string(totalMarks);
    const char *Line6 = outline.c_str();
    const char *Line7 = "Instructions:   1. Attempt all questions.\n                2. Figures to right indicate full marks.\n                3. Use sectino-wise separate answer book.\n                4. Draw neat sketches wherever necessary\n                5. Assume suitable data wherever necessary and mention them clearly.\n\n";
    const char *Line8 = "_______________________________________________________________________________";
    HPDF_Doc pdf;
    char fname[256] = "Paper.pdf";
    HPDF_Page page, page2;
    HPDF_Font def_font;
    HPDF_REAL tw, tw2, tw3, tw4, tw5, tw6, tw7;
    HPDF_REAL height;
    HPDF_REAL width;
    HPDF_UINT i;

    pdf = HPDF_New(error_handler, NULL);
    if (!pdf)
    {
        printf("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env))
    {
        HPDF_Free(pdf);
        return 1;
    }

    /* Add a new page1 object. */
    page = HPDF_AddPage(pdf);
    page2 = HPDF_AddPage(pdf);

    height = HPDF_Page_GetHeight(page); // get the height of the page
    width = HPDF_Page_GetWidth(page);   // get the width of the page
    /* Outline border of the pdf */
    HPDF_Page_SetLineWidth(page, 1);
    HPDF_Page_Rectangle(page, 10, 10, width - 20, height - 20);
    HPDF_Page_Stroke(page);

    /* Print the title of the page (with positioning center). */
    def_font = HPDF_GetFont(pdf, "Times-Roman", NULL);
    HPDF_Font font2 = HPDF_GetFont(pdf, "Times-Bold", NULL);
    HPDF_Page_SetFontAndSize(page, def_font, 28);

    height = HPDF_Page_GetHeight(page2); // get the height of the page2
    width = HPDF_Page_GetWidth(page2);   // get the width of the page2
    HPDF_Page_SetLineWidth(page2, 1);
    HPDF_Page_Rectangle(page2, 10, 10, width - 20, height - 20);
    HPDF_Page_Stroke(page2);
    def_font = HPDF_GetFont(pdf, "Times-Roman", NULL);
    HPDF_Page_SetFontAndSize(page2, def_font, 28);

    tw = HPDF_Page_TextWidth(page, Line1);                         // gets the width of the text in current fontsize, character spacing and word spacing.
    HPDF_Page_BeginText(page);                                     // begins a text object and sets the text position to (0, 0).
    HPDF_Page_TextOut(page, (width - tw) / 2, height - 50, Line1); // prints the text on the specified position.
    HPDF_Page_EndText(page);                                       // ends a text object.

    HPDF_Page_SetFontAndSize(page, def_font, 18);
    tw2 = HPDF_Page_TextWidth(page, Line2);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, (width - tw2) / 2, height - 70, Line2);
    HPDF_Page_EndText(page);

    HPDF_Page_SetFontAndSize(page, def_font, 14);
    tw3 = HPDF_Page_TextWidth(page, Line3);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, (width - tw3) / 2, height - 85, Line3);
    HPDF_Page_EndText(page);

    HPDF_Page_SetFontAndSize(page, def_font, 14);
    tw4 = HPDF_Page_TextWidth(page, Line4);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, (width - tw4) / 2, height - 100, Line4);
    HPDF_Page_EndText(page);

    HPDF_Page_SetFontAndSize(page, def_font, 14);
    tw5 = HPDF_Page_TextWidth(page, Line5);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, 20, height - 140, Line5);
    HPDF_Page_EndText(page);

    HPDF_Page_SetFontAndSize(page, def_font, 14);
    tw6 = HPDF_Page_TextWidth(page, Line6);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, 20, height - 160, Line6);
    HPDF_Page_EndText(page);

    HPDF_Page_SetFontAndSize(page, def_font, 14);
    tw7 = HPDF_Page_TextWidth(page, Line8);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, 20, height - 180, Line8);
    HPDF_Page_EndText(page);

    // output questions

    HPDF_Page_BeginText(page);
    int h = height - 220;
    HPDF_Page_MoveTextPos(page, 20, height - 220);

    HPDF_Page_BeginText(page2);
    HPDF_Page_MoveTextPos(page2, 20, height - 50);

    QuestionPaper q = QuestionPaper(noOfEasy, noOfMedium, noOfHard);
    q.createPaper();
    int count = 1;

    for (int i = 0; i < q.que.size(); i++)
    {
        string num = "";
        if (i < 9)
            num += "  ";
        num += to_string(i + 1) + ". ";

        if (i < noOfEasy)
            num += q.easy[q.que[i]];
        else if (i < (noOfEasy + noOfMedium))
            num += q.medium[q.que[i]];
        else
            num += q.hard[q.que[i]];

        int size = num.size();

        vector<string> multilineQ;
        string temp = "";

        for (int j = 0; j < size; j++)
        {
            temp += num[j];
            if (num[j] == ' ')
            {
                multilineQ.push_back(temp);
                temp = "";
            }
        }

        if (temp != "")
            multilineQ.push_back(temp);

        vector<string> t;
        temp = "";
        int cnt = 0;
        for (int j = 0; j < multilineQ.size(); j++)
        {
            cnt += multilineQ[j].size();
            temp += multilineQ[j];
            if (cnt > 85)
            {
                cnt = 0;
                t.push_back(temp);
                temp = "";
            }
        }

        if (temp != "")
            t.push_back(temp);

        HPDF_Page tlt = h < 20 ? page2 : page;

        if (noOfEasy != 0 && i == 0)
        {
            string level = " Answer the following easy questions:- (Each " + to_string(easyMarks) + " marks)";
            HPDF_Page_SetFontAndSize(tlt, font2, 14);
            HPDF_Page_ShowText(tlt, level.c_str());
            HPDF_Page_MoveTextPos(tlt, 0, -25);
            h -= 25;
        }
        else if (noOfMedium != 0 && i == (noOfEasy))
        {
            string level = " Answer the following medium questions:- (Each " + to_string(mediumMarks) + " marks)";
            HPDF_Page_SetFontAndSize(tlt, font2, 14);
            HPDF_Page_ShowText(tlt, level.c_str());
            HPDF_Page_MoveTextPos(tlt, 0, -25);
            h -= 25;
        }
        else if (noOfHard != 0 && i == (noOfEasy + noOfMedium))
        {
            string level = " Answer the following hard questions:- (Each " + to_string(hardMarks) + " marks)";
            HPDF_Page_SetFontAndSize(tlt, font2, 14);
            HPDF_Page_ShowText(tlt, level.c_str());
            HPDF_Page_MoveTextPos(tlt, 0, -25);
            h -= 25;
        }

        tlt = h < 20 ? page2 : page;

        for (int j = 0; j < t.size(); j++)
        {
            if (j != 0)
                t[j] = "      " + t[j];

            const char *question = t[j].c_str();

            HPDF_Page_SetFontAndSize(tlt, def_font, 14);
            HPDF_Page_ShowText(tlt, question);
            if (j == t.size() - 1)
                HPDF_Page_MoveTextPos(tlt, 0, -25);
            else
                HPDF_Page_MoveTextPos(tlt, 0, -15);

            if (h >= 20)
            {
                if (j == t.size() - 1)
                {
                    h -= 25;
                }
                else
                {
                    h -= 15;
                }
            }
        }
    }

    HPDF_Page_EndText(page);
    HPDF_Page_EndText(page2);

    /* clean up */
    HPDF_STATUS ok = HPDF_SaveToFile(pdf, fname);
    HPDF_Free(pdf);
    printf("PDF Generated Succefully by name Paper.pdf in the Extisting directory!\n");

    return 0;
}
