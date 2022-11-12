#include <iostream>
using namespace std;

struct friList
{
    string name;
    friList *link;
};
struct likeList
{
    string name;
    likeList *link, *prelink;
};
struct post
{
    string content, author;
    int s; // serial
    likeList *like;
    post *link, *preLink;
};
struct user
{
    string account, password;
    friList *fri;
    post *post;
    user *link, *preLink;
};

user *uhead, *upre, *ucur, *uptr;
post *phead, *pcur, *pptr;
int postSerial = 0;

int login();
bool scan_user(string); // friend
bool scan_fri(string);
int add_fri(string);
int del_fri(string);
void list_fri();
void add_post(); // post
void del_post();
void list_post(string);
int scan_like(string); // like
void dislike_post();
void list_like();

int main()
{
    uhead = new user;
    uhead->link = nullptr;
    ucur = uhead;
    // preparation
    uptr = new user;
    // set
    ucur->link = uptr;
    uptr->link = uhead->link;
    uhead->link->preLink = uptr;
    uptr->preLink = ucur;
    ucur = ucur->link;
    int keep;
    while (keep = login())
    {
        if (keep != 1)
        {
            continue;
        }
        string f;
        bool go = true;
        while (go)
        {
            // menu
            cout << "-------------------" << endl;
            cout << "[0]:logout" << endl;
            cout << "[1]:friend_list" << endl;
            cout << "[2]:add_friend" << endl;
            cout << "[3]:delete_friend" << endl;
            cout << "[4]:add_post" << endl;
            cout << "[5]:delete_post" << endl;
            cout << "[6]:watch_post" << endl;
            cout << "do: ";
            int choice;
            cin >> choice;
            switch (choice)
            {
            case 0:
                go = false;
                break;
            case 1:
                list_fri();
                break;
            case 2:
                cout << "Friend's name: ";
                cin >> f;
                add_fri(f);
                break;
            case 3:
                cout << "Friend's name: ";
                cin >> f;
                del_fri(f);
                break;
            default:
                cout << "Please try again." << endl;
                break;
            }
        }
    }
    cout << "Bye...";
    return 0;
}

int login() // return 0 == shutdown, 1 == success, 2 == error
{
    string acc, pass;
    cout << "[0]:shutdown, [1]:login, [2]:sign in: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        cout << "account: ";
        cin >> acc;
        cout << "password: ";
        cin >> pass;
        uptr = uhead->link;
        do
        {
            if (uptr->account == acc && uptr->password == pass)
            {
                cout << "\nLogin successfully." << endl;
                cout << "Your user name is " << uptr->account << endl;
                return 1;
            }
            uptr = uptr->link;
        } while (uptr != uhead->link);
        if (uptr == uhead->link)
        {
            cout << "Error." << endl;
            return 2;
        }
    case 2:
        cout << "Enter your user name to create a new account: ";
        cin >> acc;
        cout << "New password: ";
        cin >> pass;
        if (scan_user(acc))
        {
            cout << "This user name is already exist." << endl;
            return 2;
        }
        // create a new user's node
        uptr = new user;
        uptr->account = acc;
        uptr->password = pass;
        friList *fptr;
        fptr = new friList;
        uptr->fri = fptr;
        uptr->fri->link = nullptr;
        // set
        ucur->link = uptr;
        uptr->link = uhead->link;
        uhead->link->preLink = uptr;
        uptr->preLink = ucur;
        ucur = ucur->link;
        cout << "Create a new account successfully." << endl;
        return 2;
    case 0:
        return 0;

    default:
        cout << "Please try again." << endl;
        break;
    }
    return 2;
}

bool scan_user(string x)
{
    user *scanPtr;
    scanPtr = uhead->link;
    do
    {
        if (scanPtr->account == x)
        {
            return true;
        }
        scanPtr = scanPtr->link;
    } while (scanPtr != uhead->link);
    return false;
}

bool scan_fri(string x) // if friend => true, !friend => false
{
    friList *fptr;
    fptr = uptr->fri;
    while (fptr != nullptr)
    {
        if (fptr->name == x)
        {
            return true;
        }
        fptr = fptr->link;
    }
    return false;
}

int add_fri(string x)
{
    if (!scan_user(x))
    {
        cout << "\nThere is no user name " << x << "\nPlease try again." << endl;
        return 0;
    }
    if (!scan_fri(x))
    {
        friList *fptr, *fscan;
        fptr = new friList;
        fptr->name = x;
        fscan = uptr->fri;
        while (fscan->link != nullptr)
        {
            fscan = fscan->link;
        }
        fscan->link = fptr;
        fscan->link->link = nullptr;
        cout << "Add a new friend successfully" << endl;
    }
    else
    {
        cout << "You are already be in friend together." << endl;
    }
    return 0;
}

void list_fri()
{
    friList *fptr;
    cout << "----Friend List----" << endl;
    fptr = uptr->fri;
    do
    {
        cout << fptr->name << endl;
        fptr = fptr->link;
    } while (fptr != nullptr);
}

int del_fri(string x)
{
    friList *fscan, *fptr;
    fscan = uptr->fri;
    if (fscan->link == nullptr)
    {
        cout << "You don't have any friend." << endl;
        return 0;
    }
    if (scan_fri(x))
    {
        while (fscan->link->link != nullptr)
        {
            if (fscan->link->name == x)
            {
                fptr = fscan->link;
                fscan->link = fscan->link->link;
                delete fptr;
                cout << "Delete the friend successfully" << endl;
                return 0;
            }
            fscan = fscan->link;
        }
        delete fscan->link;
        fscan->link = nullptr;
        cout << "Delete the friend successfully" << endl;
    }
    else
    {
        cout << "You are already not be in friend together or there is no user name " << x << endl;
    }
    return 0;
}
