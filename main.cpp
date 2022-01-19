#include <libnotifymm.h>

#include <fstream>
#include <sstream>
#include <thread>

int toInt(std::istream& stream)
{
    std::stringstream ss;
    ss << stream.rdbuf();
    int out;
    ss >> out;

    return out;
}
std::string buildMessage(int val)
{
    std::stringstream ss;
    ss << "Battery low @ " << val;
    return ss.str();
}

int main()
{
    using namespace std::chrono_literals;

    while (true) {
        std::fstream file("/sys/class/power_supply/BAT0/capacity", std::ios::in);
        auto BAT = toInt(file);

        if (BAT <= 79) {
            Notify::init("Batgirl");
            Notify::Notification notify("Batgirl", buildMessage(BAT), "dialog-information");
            notify.show();
        }

        if (BAT <= 1)
            break;

        std::this_thread::sleep_for(10min);
    }

    return 0;
}
