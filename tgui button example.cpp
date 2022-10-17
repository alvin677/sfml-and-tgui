#include<iostream>
#include<string>
#include <TGUI/TGUI.hpp>
#include <stdio.h>

//Print Something on the Concole
void print_Someting(std::string text)
{
    std::cout << text;
};

//Create a Button and Call the print_Something function.
void MakeButton(std::string ButtonText, tgui::GuiBase& gui)
{
    auto button = tgui::Button::create(ButtonText);
    button->setSize({ "50%", "16.67%" });
    button->setPosition({ "25%", "70%" });
    //button->getRenderer()->setBackgroundColor({ 0, 255, 0, 175 });
    button->getRenderer()->setBackgroundColorHover({ 255, 0, 0, 175 });
    FILE* file;
    if (file = fopen("password.txt", "r")) {
        fclose(file);
        std::cout << "File exists";
        //button->getRenderer()->setBackgroundColorHover({ 0, 0, 255, 175 });
    }
    gui.add(button);
    button->onPress(print_Someting, "Hello World\n");
}


//For a easy debugging will show if a file counld not be opened in the console.
bool RunGUI(tgui::GuiBase& gui)
{
    try
    {
        MakeButton("Click Me", gui);
        return true;
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return false;
    }
}



//main entry
int main()
{
    sf::RenderWindow window{ {800, 600}, "codeSaver" };

    //A Gui Object that works with Sfml window.
    tgui::GuiSFML gui{ window };

    gui.loadWidgetsFromFile("form.txt");

    RunGUI(gui);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            gui.handleEvent(event);
                
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        gui.draw();
        window.display();
        auto buttonPtr = gui.get<tgui::Button>("mordin");
        //buttonPtr->getRenderer()->setBackgroundColor({ 255, 150, 0, 175 });
        //buttonPtr->onPress();

        for (const tgui::Widget::Ptr& widget : gui.getWidgets())
        {
            auto button = widget->cast<tgui::Button>();
            if (button)  // If widget isn't a Button then 'button' will be nullptr
            {
                std::cout << button->getWidgetName() << std::endl;
                button->getRenderer()->setBackgroundColor(tgui::Color::Blue);
            }
        }
    }
}








/*
#include <iostream>
#include <string>

int main()
{
    std::string str = "<paste_key>hv617j1t</paste_key>";
    int end = str.find("</paste_key>");
    str.erase(0, 11);
    str.erase(end - 11, 12);
    std::cout << str;
    system("pause >nul");

    
    std::string cmd1 = "curl -X POST -d \"api_dev_key=i7iRqhDHWIl8pF53TtzZ1lrElehjbN4n\" -d \"api_user_key=7d304e6c4a2efac0133cba3773c3f54a\" -d \"api_option=list\" -d \"api_results_limit=1000\" \"https://pastebin.com/api/api_post.php\"";
    system(cmd1.c_str());
    std::cout << "\n\n";

    std::string fileName;
    std::string fileContent;

    std::cout << "Enter name: "; getline(std::cin, fileName);
    std::cout << "Enter content: "; getline(std::cin, fileContent);

    std::string cmd = "curl -X POST -d \"api_dev_key=i7iRqhDHWIl8pF53TtzZ1lrElehjbN4n\" -d \"api_option=paste\" -d \"api_user_key=7d304e6c4a2efac0133cba3773c3f54a\" \"https://pastebin.com/api/api_post.php\" -d \"api_expire_date=N\" -d \"api_paste_name=" + fileName + "\" -d \"api_paste_code=" + fileContent + "\"";
    system(cmd.c_str());

    system("pause >nul");
}
*/
