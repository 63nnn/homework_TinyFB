
// Github: https://github.com/63nnn/homework_TinyFB/tree/main/221114
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
    int s = 0; // serial
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
int postSerial = 0;

int login();
bool scan_user(string); // friend, para:user
bool scan_fri(string);  // para:user
int add_fri(string);    // para:user
int del_fri(string);    // para:user
void list_fri();
void add_post(); // post
int del_post();
int list_post(string); // para:user
int like_post(int);    // like, para:postNum
int dislike_post(int); // para:postNum
int list_like(int);    // para:postNum
int disdis(string);    // para:user

int main()
{
    // preparation
    uhead = new user;
    uhead->link = nullptr;
    ucur = uhead;
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
        int n;
        bool go = true;
        while (go)
        {
            // menu
            cout << "===================" << endl;
            cout << "[0]:logout" << endl;
            cout << "[1]:friend_list" << endl;
            cout << "[2]:add_friend" << endl;
            cout << "[3]:delete_friend" << endl;
            cout << "[4]:add_post" << endl;
            cout << "[5]:delete_post" << endl;
            cout << "[6]:watch_post" << endl;
            cout << "[7]:like_post" << endl;
            cout << "[8]:dislike_post" << endl;
            cout << "[9]:like_list" << endl;
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
            case 4:
                add_post();
                break;
            case 5:
                del_post();
                break;
            case 6:
                cout << "Whose post: ";
                cin >> f;
                list_post(f);
                break;
            case 7:
                cout << "Which post: ";
                cin >> n;
                like_post(n);
                break;
            case 8:
                cout << "Which post: ";
                cin >> n;
                dislike_post(n);
                break;
            case 9:
                cout << "Which post: ";
                cin >> n;
                list_like(n);
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
        // friend list head
        friList *fptr;
        fptr = new friList;
        uptr->fri = fptr;
        uptr->fri->link = nullptr;
        // post list head
        post *pptr;
        pptr = new post;
        uptr->post = pptr;
        uptr->post->link = nullptr;
        // set
        ucur->link = uptr;
        uptr->link = uhead->link;
        uhead->link->preLink = uptr;
        uptr->preLink = ucur;
        ucur = ucur->link;
        cout << ">> Create a new account successfully." << endl;
        return 2;
    case 0:
        return 0;

    default:
        cout << "Please try again." << endl;
        break;
    }
    return 2;
}

bool scan_user(string x) // user exist => true
{
    user *uscan;
    uscan = uhead->link;
    do
    {
        if (uscan->account == x)
        {
            return true;
        }
        uscan = uscan->link;
    } while (uscan != uhead->link);
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
        while (fscan->link != nullptr) // Find the last one
        {
            fscan = fscan->link;
        }
        fscan->link = fptr;
        fscan->link->link = nullptr;
        cout << ">> Add a new friend successfully" << endl;
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
    cout << "====Friend List====" << endl;
    fptr = uptr->fri->link;
    while (fptr != nullptr)
    {
        cout << fptr->name << endl;
        fptr = fptr->link;
    }
}

int del_fri(string x)
{
    friList *fscan, *fptr;
    fscan = uptr->fri;
    if (fscan->link == nullptr) // nullptr == no friend
    {
        cout << "You don't have any friend." << endl;
        return 0;
    }
    if (scan_fri(x))
    {
        while (fscan->link->link != nullptr)
        {
            if (fscan->link->name == x) // friend's name
            {
                fptr = fscan->link;
                fscan->link = fscan->link->link;
                delete fptr;
                disdis(x); // dislike
                cout << ">> Delete the friend successfully" << endl;
                return 0;
            }
            fscan = fscan->link;
        }
        delete fscan->link;
        fscan->link = nullptr;
        disdis(x); // dislike
        cout << ">> Delete the friend successfully" << endl;
    }
    else
    {
        cout << "You are already not be in friend together or there is no user name " << x << endl;
    }
    return 0;
}

void add_post()
{
    cout << "What do you want to share?(less than 64 letters)\n: ";
    char keyin[100];
    cin.get();              // clean buffer
    cin.getline(keyin, 64); // whole string
    string content = keyin;
    post *pptr;
    pptr = new post;
    // author
    pptr->author = uptr->account;
    // content
    pptr->content = content;
    // like list head
    likeList *lptr;
    lptr = new likeList;
    pptr->like = lptr;
    pptr->like->link = nullptr;
    // the number
    pptr->s = postSerial;
    postSerial += 1;
    // set
    post *pscan;
    pscan = uptr->post;
    while (pscan->link != nullptr) // find last node
    {
        pscan = pscan->link;
    }
    pscan->link = pptr;
    pptr->preLink = pscan;
    pscan->link->link = nullptr;
    cout << ">> The post upload successfully." << endl;
}

int list_post(string who)
{
    if (!scan_fri(who) && who != uptr->account) // permission
    {
        cout << "You are not a friend." << endl;
        return 0;
    }
    cout << "=====Post List=====" << endl;
    user *whoptr;
    whoptr = uhead->link;
    do // find who
    {
        if (whoptr->account == who)
        {
            post *pptr;
            pptr = whoptr->post->link;
            while (pptr != nullptr) // print every post
            {
                cout << "Post" << pptr->s << endl;
                cout << pptr->author << ": " << endl;
                cout << pptr->content << endl;
                cout << "-------------------" << endl;
                pptr = pptr->link;
            }
            return 0;
        }
        whoptr = whoptr->link;
    } while (whoptr != uhead->link);
    if (whoptr == uhead->link) // the user doesn't exist
    {
        cout << "Error." << endl;
    }
    return 0;
}

int del_post()
{
    int snum;
    cout << "Which post do you want to delete? (Post number): ";
    cin >> snum;
    post *pptr;
    pptr = uptr->post->link;
    while (pptr != nullptr) // find the post
    {
        if (pptr->s == snum)
        {
            if (pptr->author != uptr->account) // permission
            {
                cout << "Permission denied." << endl;
                return 0;
            }
            pptr->preLink->link = pptr->link;
            if (pptr->link != nullptr) // null
            {
                pptr->link->preLink = pptr->preLink;
            }
            cout << ">> Delete the post successfully." << endl;
            return 0;
        }
        pptr = pptr->link;
    }
    cout << "Error." << endl;
    return 0;
}

int like_post(int o)
{
    user *whoptr;
    whoptr = uhead->link->link; // !
    do
    {
        post *pptr;
        pptr = whoptr->post->link; // !
        while (pptr != nullptr)
        {
            if (pptr->s == o)
            {
                if (!scan_fri(whoptr->account) && whoptr->account != uptr->account) // permission
                {
                    cout << "You should be friend first." << endl;
                    return 0;
                }
                likeList *lptr, *lscan;
                lptr = new likeList;
                lptr->name = uptr->account;
                // set
                lscan = pptr->like;
                while (lscan->link != nullptr)
                {
                    lscan = lscan->link;
                }
                lscan->link = lptr;
                lptr->link = nullptr;
                lptr->prelink = lscan;
                cout << "Liked." << endl;
                return 0;
            }
            pptr = pptr->link;
        }
        whoptr = whoptr->link;
    } while (whoptr != uhead->link);
    cout << "Error." << endl;

    return 0;
}

int list_like(int o)
{
    user *whoptr;
    whoptr = uhead->link->link;
    cout << "===================" << endl;
    do // find the user
    {
        post *pptr;
        pptr = whoptr->post->link;
        while (pptr != nullptr) // find the post
        {
            if (pptr->s == o)
            {
                if (!scan_fri(whoptr->account) && whoptr->account != uptr->account) // permission
                {
                    cout << "You should be friend first." << endl;
                    return 0;
                }
                likeList *lptr;
                lptr = pptr->like->link;
                cout << "Post" << pptr->s << "'s likelist:" << endl; // post000?
                while (lptr != nullptr)                              // find the last like
                {
                    cout << lptr->name << endl;
                    lptr = lptr->link;
                }
                return 0;
            }
            pptr = pptr->link;
        }
        whoptr = whoptr->link;
    } while (whoptr != uhead->link);
    cout << "Error." << endl;

    return 0;
}

int dislike_post(int o)
{
    user *whoptr;
    whoptr = uhead->link->link;
    do // find the user
    {
        post *pptr;
        pptr = whoptr->post->link;
        while (pptr != nullptr) // find the post
        {
            if (pptr->s == o)
            {
                likeList *lptr;
                lptr = pptr->like->link;
                while (lptr != nullptr) // find the like
                {
                    if (lptr->name == uptr->account)
                    {
                        lptr->prelink->link = lptr->link;
                        if (lptr->link != nullptr)
                        {
                            lptr->link->prelink = lptr->prelink;
                        }
                    }
                    lptr = lptr->link;
                }
                cout << "Disliked." << endl;
                return 0;
            }
            pptr = pptr->link;
        }
        whoptr = whoptr->link;
    } while (whoptr != uhead->link);
    cout << "Error." << endl;

    return 0;
}

int disdis(string x)
{
    user *whoptr;
    whoptr = uhead->link->link;
    do // find the user
    {
        if (whoptr->account == x)
        {
            post *pptr;
            pptr = whoptr->post->link;
            while (pptr != nullptr) // all post
            {
                likeList *lptr;
                lptr = pptr->like->link;
                while (lptr != nullptr) // find the like
                {
                    if (lptr->name == uptr->account)
                    {
                        lptr->prelink->link = lptr->link;
                        if (lptr->link != nullptr)
                        {
                            lptr->link->prelink = lptr->prelink;
                        }
                    }
                    lptr = lptr->link;
                }
                pptr = pptr->link;
            }
            return 0;
        }
        whoptr = whoptr->link;
    } while (whoptr != uhead->link);
    cout << "Error." << endl;

    return 0;
}