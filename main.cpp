#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

// ========================
//       USER CLASS
// ========================
class User {
private:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;
    
public:
    User() {
        username = "";
        password = "";
        phoneNumber = "";
        status = "Offline";
        lastSeen = "Never";
    }
    
    User(string uname, string pwd, string phone) {
        username = uname;
        password = pwd;
        phoneNumber = phone;
        status = "Offline";
        updateLastSeen();
    }
    
    string getUsername() const {
        return username;
    }
    
    string getPhoneNumber() const {
        return phoneNumber;
    }
    
    string getStatus() const {
        return status;
    }
    
    string getLastSeen() const {
        return lastSeen;
    }
    
    void setStatus(string newStatus) {
        status = newStatus;
        if (newStatus == "Offline") {
            updateLastSeen();
    }
    
    void setPhoneNumber(string phone) {
         phoneNumber = phone;
    }
    
    void updateLastSeen() {
        time_t now = time(0);
        lastSeen = ctime(&now);
    }
    
    bool checkPassword(string pwd) const {
         if (password == pwd) {
        return true;
    }
    return false;
    }
    
    void changePassword(string newPwd) {
        password = newPwd;
    }
};

// ========================
//      MESSAGE CLASS
// ========================
class Message
{
private:
    string sender;
    string content;
    string timestamp;
    string status;
    Message *replyTo;

public:
    Message()
    {
        // TODO: Implement default constructor
    }

    Message(string sndr, string cntnt)
    {
        // TODO: Implement parameterized constructor
    }

    string getContent() const
    {
        // TODO: Implement getter
        return "";
    }

    string getSender() const
    {
        // TODO: Implement getter
        return "";
    }

    string getTimestamp() const
    {
        // TODO: Implement getter
        return "";
    }

    string getStatus() const
    {
        // TODO: Implement getter
        return "";
    }

    Message *getReplyTo() const
    {
        // TODO: Implement getter
        return nullptr;
    }

    void setStatus(string newStatus)
    {
        // TODO: Implement setter
    }

    void setReplyTo(Message *msg)
    {
        // TODO: Implement setter
    }

    void updateTimestamp()
    {
        // TODO: Implement timestamp update
    }

    void display() const
    {
        // TODO: Implement message display
    }

    void addEmoji(string emojiCode)
    {
        // TODO: Implement emoji support
    }
};

// ========================
//       CHAT CLASS (BASE)
// ========================
class Chat
{
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;

public:
    Chat()
    {
        // TODO: Implement default constructor
        chatName = "Untitled Chat";
    }

    Chat(vector<string> users, string name)
    {
        // TODO: Implement parameterized constructor
        participants = users;
        chatName = name;
    }

    void addMessage(const Message &msg)
    {
        // TODO: Implement message addition
        messages.push_back(msg);
    }

    bool deleteMessage(int index, const string &username)
    {
        // TODO: Implement message deletion
        if (index >= 0 && index < messages.size())
        {
            messages.erase(messages.begin() + index);
            cout << "Message deleted" << endl;
            return true;
        }
        else
        {
            cout << "Error: You can only delete your own messages." << endl;
            return false;
        }
        cout << "Error: Invalid message index." << endl;
        return false;
    }

    virtual void displayChat() const
    {
        // TODO: Implement chat display
        cout << "\n--- Chat: " << chatName << " ---" << endl;
        if (messages.empty())
        {
            cout << "No messages yet." << endl;
        }
        else
        {
            for (const auto &msg : messages)
            {
                msg.display();
            }
        }
        cout << "-------------------------" << endl;
    }

    vector<Message> searchMessages(string keyword) const
    {
        // Searches for messages containing a specific keyword.
        vector<Message> foundMessages;
        for (const auto &msg : messages)
        {
            if (msg.getContent().find(keyword) != string::npos)
            {
                foundMessages.push_back(msg);
            }
        }
        return foundMessages;
    }

    void exportToFile(const string &filename) const
    {
        // Exports the entire chat history to a text file.
        ofstream outFile(filename);
        if (outFile.is_open())
        {
            outFile << "Chat History: " << chatName << endl;
            outFile << "=========================" << endl;
            for (const auto &msg : messages)
            {
                outFile << "[" << msg.getTimestamp() << "] "
                        << msg.getSender() << ": "
                        << msg.getContent() << endl;
            }
            outFile.close();
            cout << "Chat history exported to " << filename << endl;
        }
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat {
private:
    string user1;
    string user2;

public:
    PrivateChat(string u1, string u2) {
        user1 = u1;
        user2 = u2;
        participants = {u1, u2};
        chatName = u1 + " & " + u2;
    }

    void displayChat() const override {
        cout << "\n=== Private Chat: " << user1 << " & " << user2 << " ===" << endl;

        if (messages.empty()) {
            cout << "No messages yet. Start the conversation!" << endl;
        } else {
            for (const auto& msg : messages) {
                msg.display();
            }
        }
        cout << endl;
    }

    void showTypingIndicator(const string& username) const {
        cout << username << " is typing..." << endl;
    }
};

// ========================
//      GROUP CHAT CLASS
// ========================
class GroupChat : public Chat {
private:
    vector<string> admins;
    string description;

public:
    GroupChat(vector<string> users, string name, string creator) {
        participants = users;
        chatName = name;
        admins.push_back(creator);
        description = "";
    }

    void addAdmin(string newAdmin) {
        if (find(admins.begin(), admins.end(), newAdmin) == admins.end()) {
            if (find(participants.begin(), participants.end(), newAdmin) != participants.end()) {
                admins.push_back(newAdmin);
                cout << newAdmin << " has been added as admin." << endl;
            } else {
                cout << "User is not a participant in this group." << endl;
            }
        } else {
            cout << "User is already an admin." << endl;
        }
    }

    bool removeParticipant(const string& admin, const string& userToRemove) {
        if (!isAdmin(admin)) {
            cout << "Only admins can remove participants." << endl;
            return false;
        }

        auto it = find(participants.begin(), participants.end(), userToRemove);
        if (it != participants.end()) {
            participants.erase(it);

            // Also remove from admins if they were admin
            auto adminIt = find(admins.begin(), admins.end(), userToRemove);
            if (adminIt != admins.end()) {
                admins.erase(adminIt);
            }

            cout << userToRemove << " has been removed from the group." << endl;
            return true;
        }

        cout << "User not found in the group." << endl;
        return false;
    }

    bool isAdmin(string username) const {
        return find(admins.begin(), admins.end(), username) != admins.end();
    }

    bool isParticipant(string username) const {
        return find(participants.begin(), participants.end(), username) != participants.end();
    }

    void setDescription(string desc) {
        description = desc;
    }

    void displayChat() const override {
        cout << "\n=== Group Chat: " << chatName << " ===" << endl;
        if (!description.empty()) {
            cout << "Description: " << description << endl;
        }

        cout << "Participants (" << participants.size() << "): ";
        for (size_t i = 0; i < participants.size(); i++) {
            cout << participants[i];
            if (isAdmin(participants[i])) {
                cout << " (Admin)";
            }
            if (i < participants.size() - 1) cout << ", ";
        }
        cout << "\n" << endl;

        if (messages.empty()) {
            cout << "No messages yet. Start the conversation!" << endl;
        } else {
            for (const auto& msg : messages) {
                msg.display();
            }
        }
        cout << endl;
    }

    void sendJoinRequest(const string& username) {
        if (!isParticipant(username)) {
            participants.push_back(username);
            cout << username << " has joined the group." << endl;
        } else {
            cout << "User is already in the group." << endl;
        }
    }

    void addParticipant(const string& admin, const string& newUser) {
        if (isAdmin(admin)) {
            sendJoinRequest(newUser);
        } else {
            cout << "Only admins can add participants." << endl;
        }
    }

    vector<string> getAdmins() const { return admins; }
    string getDescription() const { return description; }
};
// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp
{
private:
    vector<User> users;
    vector<Chat *> chats;
    int currentUserIndex;

    int findUserIndex(string username) const
    {
        // TODO: Implement user search
        return -1;
    }

    bool isLoggedIn() const
    {
        // TODO: Implement login check
        return false;
    }

    string getCurrentUsername() const
    {
        // TODO: Implement get current user
        return "";
    }

public:
    WhatsApp() : currentUserIndex(-1) {}

    void signUp()
    {
        // TODO: Implement user registration
    }

    void login()
    {
        // TODO: Implement user login
    }

    void startPrivateChat()
    {
        // TODO: Implement private chat creation
    }

    void createGroup()
    {
        // TODO: Implement group creation
    }

    void viewChats() const
    {
        // TODO: Implement chat viewing
    }

    void logout()
    {
        // TODO: Implement logout
    }

    void run()
    {
        while (true)
        {
            if (!isLoggedIn())
            {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1)
                    login();
                else if (choice == 2)
                    signUp();
                else if (choice == 3)
                    break;
            }
            else
            {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1)
                    startPrivateChat();
                else if (choice == 2)
                    createGroup();
                else if (choice == 3)
                    viewChats();
                else if (choice == 4)
                    logout();
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main()
{
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}