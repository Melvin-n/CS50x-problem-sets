#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool checkPair(int, int);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }

    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++) //for the number of ranks given, for the ith rank
    {

        for (int j = 1; j < candidate_count - i; j++) //for number of ranks lower than ith rank
        {
            preferences[ranks[i]][ranks[i + j]]++;
        }
    }
}
// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i ++)
    {
        for (int j = 0; j < candidate_count; j ++)
        {
            if (preferences[i][j + i] > preferences[j + i][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j + i;
                pair_count ++;
            }
            else if (preferences[j + i][i] > preferences[i][j + i])
            {
                pairs[pair_count].winner = j + i;
                pairs[pair_count].loser = i;
                pair_count ++;
            }

        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0 + i; j < pair_count; j++)
        {
            pair current = pairs[i];
            if (preferences[pairs[i].winner] - preferences[pairs[i].loser] > preferences[pairs[j].winner] - preferences[pairs[j].loser])
            {
                pairs[i] = pairs[j];
                pairs[j] = current;

            }
        }
    }

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++) //looping through the pairs
    {
        int j = pairs[i].loser;
        if (checkPair(pairs[i].winner, j)) //
        {
            locked[pairs[i].winner][j] = true;
        }
        else
        {
            locked[pairs[i].winner][j] = false;
        }
    }

}
//recursion function
bool checkPair(i, j)
{
    for (int x = 0; x < candidate_count; x ++) //looping through each candidate in ith row
    {
        if (locked[x][i]) // x == iterator, i stays constant in these iterations
        {
            if (j == x)
            {
                return false;
            }
            return checkPair(x, j); //j = loser of i?
        }

    }
    return true;
}
//Print the winner of the election
void print_winner(void)
{
    // TODO
    int current = 0;
    int top[pair_count];
    int found = 0;
    bool flag = false;


    for (int i = 0; i < candidate_count; i ++)
    {
        flag = false;
        for (int j = 0; j < candidate_count; j ++)
        {
            if (locked[j][i] == true)
            {
                flag = true;
            }

        }
        if (flag == false)
        {
            string source = candidates[i];
            printf("%s\n", source);

        }

    }


}

