#include <bits/stdc++.h>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    int i; cin>>i;
    cout << "You entered: " << i << endl;
    cout << "Message: \n";
    while(i--)
    {
        for (const string& word : msg)
        {
            cout << word << " ";
        }
        cout<<endl;
    }
    cout << endl;
}
