// Libraries
#include <iostream>
#include <string>
#include <TGUI/TGUI.hpp>
#include <fstream>
#include <vector>
#include <Windows.h>

// Variables
sf::RenderWindow window{ {800, 600}, "TGUI window with SFML" };
tgui::GuiSFML gui{ window };
int ConfirmValue = 0;
std::vector<tgui::Button::Ptr> PastebinList;
std::vector<std::string> Script;

//For a easy debugging will show if a file counld not be opened in the console.
bool RunGUI(tgui::GuiBase& gui)
{
    try
    {
        //MakeButton("Click Me", gui);
        return true;
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return false;
    }
}

// Function runs whenever a button is clicked on (basically it loads in the code from the pastebin link)
void idclicked(int id) {

    std::cout << id;
    auto Input = gui.get<tgui::TextArea>("Code");
    // 

    char psBuffer[128];
    FILE* pPipe;
    std::string output;

    std::string cmd = "curl https://pastebin.com/raw/" + Script[id];
    if ((pPipe = _popen(cmd.c_str(), "rt")) == NULL)
        exit(1);

    while (fgets(psBuffer, 256, pPipe))
    {
        output = output + psBuffer;
    }

    system("cls");
    size_t c;
    while ((c = output.find("@n")) != -1) {
        output.replace(c, 2, "\n");
    }
    //
    std::cout << cmd;
    Input->setText(output);
} //prints id of button


// This function will re-read the text file with the pastebin ids
void RefreshPastebin() {
    PastebinList.clear();
    Script.clear();
    std::string content;

    // The script variable will in this case be used to store each script. The vector can be used to find out the length and then we'll know how many buttons to load.
    int y = 10;
    auto list = gui.get<tgui::ScrollablePanel>("Scripts"); //scroll

    std::ifstream file;

    file.open("pastebins.txt");
    while (getline(file, content)) { std::cout << content << "\n"; Script.push_back(content); }
    file.close();

    for (int i = 0; i < Script.size(); i++) {
        auto newButton = tgui::Button::create();
        newButton->setSize("80%", "3%");
        newButton->setPosition(10, y);
        newButton->setText(Script[i]);

        PastebinList.push_back(newButton);  
        list->add(newButton); // adds new button to list
        std::cout << y << std::endl;
        y += 45;
        PastebinList[i]->onPress(idclicked, i);
    }//creats button to list

} 

void NewFileFunction() {
    auto newFile = gui.get<tgui::ChildWindow>("NewFile");

    newFile->setEnabled(true);
    newFile->setVisible(true);       
}//for creats new file button

void CancelFunction() {
    auto newFile = gui.get<tgui::ChildWindow>("NewFile");

    newFile->setEnabled(false);
    newFile->setVisible(false);
} //cancel for new file funtion

void ConfirmFunction() {
    CancelFunction();
    auto Input = gui.get<tgui::TextArea>("Code");

    Input->setText("");
}//confirm for new file function

void UploadFunction() {
    auto UploadFile = gui.get<tgui::ChildWindow>("UploadFile");
    auto Text2 = gui.get<tgui::Label>("Text2");
    ConfirmValue = 1;
    UploadFile->setEnabled(true);
    UploadFile->setVisible(true);
    Text2->setText("Upload file as");
}//for uppload button

void Cancel2Function() {
    auto UploadFile = gui.get<tgui::ChildWindow>("UploadFile");
    auto UploadName = gui.get<tgui::EditBox>("UploadName");;

    UploadName->setText("");
    UploadFile->setEnabled(false);
    UploadFile->setVisible(false);
}//cancel for upload file function

void Confirm2Function() {
    // Confirm button for Uploading
    if (ConfirmValue == 1) {
        auto UploadName = gui.get<tgui::EditBox>("UploadName");
        auto Input = gui.get<tgui::TextArea>("Code");

        std::string fileName = UploadName->getText().toStdString();
        std::string fileContent = Input->getText().toStdString();
        
        std::cout << fileContent;
        std::cout << std::endl;

        size_t c;
        while ((c = fileContent.find("\n")) != -1) {
            fileContent.replace(c, 1, "@n");
        }

        std::string cmd = "curl -X POST -d \"api_dev_key=i7iRqhDHWIl8pF53TtzZ1lrElehjbN4n\" -d \"api_option=paste\" -d \"api_user_key=7d304e6c4a2efac0133cba3773c3f54a\" \"https://pastebin.com/api/api_post.php\" -d \"api_expire_date=N\" -d \"api_paste_name=" + fileName + "\" -d \"api_paste_code=" + fileContent + "\"";
        system(cmd.c_str());
    }

    // Confirm button for Saving
    else if (ConfirmValue == 2) {
        auto Name = gui.get<tgui::EditBox>("UploadName");
        auto Input = gui.get<tgui::TextArea>("Code");
        
        std::cout << Name->getText().toStdString();
        std::ofstream file(Name->getText().toStdString());
        std::string text = Input->getText().toStdString();
        if (file.is_open())
        {
            file << text;
            file.close();
        }
    }

    Cancel2Function();
}

void SaveFunction() {
    auto UploadFile = gui.get<tgui::ChildWindow>("UploadFile");
    auto Text2 = gui.get<tgui::Label>("Text2");
    ConfirmValue = 2;

    UploadFile->setEnabled(true);
    UploadFile->setVisible(true);
    Text2->setText("Save file as");
}//save for uppload function

void button(){
    //buttons
    auto New = gui.get<tgui::Button>("New");
    auto Cancel = gui.get<tgui::Button>("Cancel");
    auto Confirm = gui.get<tgui::Button>("Confirm");
    //Functions for buttons
    New->onPress(NewFileFunction);
    Cancel->onPress(CancelFunction);
    Confirm->onPress(ConfirmFunction);  

    //Buttons for childwindow
    auto Upload = gui.get<tgui::Button>("Upload");
    auto Cancel2 = gui.get<tgui::Button>("Cancel2");
    auto Confirm2 = gui.get<tgui::Button>("Confirm2");
    //Functions for buttons
    Upload->onPress(UploadFunction);
    Cancel2->onPress(Cancel2Function);
    Confirm2->onPress(Confirm2Function);

    auto Save = gui.get<tgui::Button>("Save");
    Save->onPress(SaveFunction);

    auto Refresh = gui.get<tgui::Button>("Refresh");
    Refresh->onPress(RefreshPastebin);
}



//main entry
int main()
{

    gui.loadWidgetsFromFile("form.txt");

    button(); //make button functions
    RefreshPastebin();
    RunGUI(gui);

    while (window.isOpen())
    {
        //Sleep(10);
        sf::Event event;
        while (window.pollEvent(event))
        {
            gui.handleEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(80, 80, 80, 255));
        gui.draw();
        window.display();
    }
}
