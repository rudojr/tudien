#include <iostream>

#include <string>

using namespace std;

void print();

struct Struktura

{

  int rightside;

  string rules;

  string rs;

};

struct Struktura2

{

  int len;

};

int numOfRules, i, j, m, k, counter = 0, counter2, numOfFacts, stalker, step = 0;

string fakti[100], object, facts, rule, R[100][100], ans;

bool done = false;

Struktura p1[100], Rules[100][100];

Struktura2 gol[100];

int main()

{

  cout << "Enter the facts: ";

  cin >> facts;

  numOfFacts = facts.size();

  for (i = 0; i <= facts.size() - 1; i++)

  {

    fakti[i] = toupper(facts.at(i));

  }

  cout << "Enter the objective: ";

  cin >> object;

  for (i = 0; i < object.size(); i++)

  {

    object.at(i) = toupper(object.at(i));

  }

  cout << "How many rules do you have?: ";

  cin >> numOfRules;

  for (i = 0; i <= numOfRules - 1; i++)

  {

    cout << "Enter rule " << i + 1 << ": ";

    cin >> rule;

    gol[i].len = rule.size() - 1;

    for (j = 0; j <= rule.size() - 1; j++)

    {

      if (j == rule.size() - 1)

      {

        p1[i].rs = toupper(rule.at(j));

      } else

      {

        R[i][j] = toupper(rule.at(j));

      }

    }

  }

  print();

  cout << "\nDo you want to add another rule? (y/n): ";

  cin >> ans;

  if (ans == "Y" || ans == "y")

  {

    cout << "\nEnter how many rules do you want to add: ";

    cin >> k;

    for (i = numOfRules; i <= numOfRules + k - 1; i++)

    {

      cout << "Enter rule " << i + 1 << ": ";

      cin >> rule;

      gol[i].len = rule.size() - 1;

      for (j = 0; j <= rule.size() - 1; j++)

      {

        if (j == rule.size() - 1)

        {

          p1[i].rs = toupper(rule.at(j));

        } else

        {

          R[i][j] = toupper(rule.at(j));

        }

      }

    }

    numOfRules = numOfRules + k;

    print();

  }

  ans = "Y";

  while (ans == "Y" || ans == "y")

  {

    cout << "\nDo you want to remove a rule?(y/n): ";

    cin >> ans;

    if (ans != "Y" && ans != "y")

    {

      break;

    }

    cout << "\nEnter the number of the rule: ";

    cin >> k;

    for (i = k - 1; i <= numOfRules - 1; i++)

    {

      gol[i].len = gol[i + 1].len;

      for (j = 0; j <= gol[i].len; j++)

      {

        if (j == gol[i].len)

        {

          p1[i].rs = p1[i + 1].rs;

        } else

        {

          R[i][j] = R[i + 1][j];

        }

      }

    }

    numOfRules = numOfRules - 1;

    print();

  }

  ans = "Y";

  while (ans == "Y" || ans == "y")

  {

    cout << "\nDo you want to change something(y/n): ";

    cin >> ans;

    if (ans != "Y" && ans != "y")

    {

      break;

    }

    cout << "\nEnter the number of the rule: ";

    cin >> i;

    cout << "\nEnter new rule " << i << ": ";

    cin >> rule;

    gol[i - 1].len = rule.size() - 1;

    for (j = 0; j <= rule.size() - 1; j++)

    {

      if (j == rule.size() - 1)

      {

        p1[i - 1].rs = toupper(rule.at(j));

      } else

      {

        R[i - 1][j] = toupper(rule.at(j));

      }

    }

  }

  print();

  cout << endl << endl << endl;

  cout << "Solution: " << endl << endl;

  stalker = numOfFacts + 1;

  while (done == false)

  {

    done = true;

    for (i = 0; i <= numOfRules - 1; i++)

    {

      counter = 0;

      counter2 = 0;

      for (j = 0; j <= gol[i].len - 1; j++)

      {

        for (k = 0; k <= numOfFacts - 1; k++)

        {

          if (fakti[k] == R[i][j])

          {

            counter++;

          }

          if (counter == gol[i].len)

          {

            for (m = 0; m <= numOfFacts - 1; m++)

            {

              if (p1[i].rs == fakti[m])

              {

                counter2++;

              }

            }

            if (counter2 == 0)

            {

              fakti[numOfFacts] = p1[i].rs;

              numOfFacts++;

              step++;

              cout << "Rule " << i + 1 << ": ";

              for (m = 0; m <= gol[i].len - 1; m++)

              {

                cout << R[i][m];

                if (m == gol[i].len - 1)

                {

                  cout << "";

                } else

                {

                  cout << " ^ ";

                }

              }

              cout << " -> " << p1[i].rs << endl;

              cout << "Set of facts: { ";

              for (m = 0; m <= numOfFacts - 1; m++)

              {

                cout << fakti[m];

                if (m != numOfFacts - 1)

                  cout << ",";

              }

              cout << " }";

              cout << endl;

              done = false;

            }

          }

          for (m = 0; m <= numOfFacts - 1; m++)

          {

            if (fakti[m] == object)

            {

              done = true;

            }

          }

        }

      }

    }

  }

  counter = 0;

  for (m = 0; m <= numOfFacts - 1; m++)

  {

    if (fakti[m] == object)

      counter++;

  }

  if (counter == 0)

    cout << "Sorry, the objective was not found!\n";

  else

  if (step > 1)

  {

    cout << "\nThe objective was found in " << step + 1 << " steps!\n\n";

  } else cout << "\nThe objective was found in " << step + 1 << " step!\n\n";

  system("pause");

  return 0;

}

void print()

{

  cout << endl << endl << endl;

  cout << "Exercise: " << endl << endl;

  cout << "Set of facts: { ";

  for (i = 0; i <= numOfFacts - 1; i++)

  {

    cout << fakti[i];

    if (i != numOfFacts - 1)

      cout << ",";

  }

  cout << " }";

  cout << "\nObjective: " << object << endl;

  for (i = 0; i <= numOfRules - 1; i++)

  {

    cout << "Rule " << i + 1 << ": ";

    for (j = 0; j <= gol[i].len - 1; j++)

    {

      cout << R[i][j];

      if (j != gol[i].len - 1)

        cout << " ^ ";

    }

    if (gol[i].len != 0)

    {

      cout << " -> ";

    }

    cout << p1[i].rs;

    cout << endl;

  }

}
