
struct voteparameters
{   
    string name<64>;
    int voterid;
};

program VOTECLIENT_PROG
{
        version VOTECLIENT_VERS
        {
        string ZEROIZE() = 1;
        string ADDVOTER(int) = 2;
        string VOTEFOR(voteparameters) = 3;
        string LISTCANDIDATES() = 4;
        int VOTECOUNT(string) = 5;
        } = 1;
} = 0x8323804;
