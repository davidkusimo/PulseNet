#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "common/Protocol.h"
#include "common/UdpSocket.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    // Check if the user provided an ECU type
    if (argc < 2) {
        cout << "Usage: ./ecu_node [engine|brakes|doors|lights]" << endl;
        return 1;
    }

    string type = argv[1];
    uint32_t my_id;
    float simulated_value = 0.0f;

    // Assign ID based on the argument
    if (type == "engine") {
        my_id = ID_ENGINE;
        simulated_value = 2500.0f; // Initial RPM
    } else if (type == "brakes") {
        my_id = ID_BRAKES;
        simulated_value = 0.0f;    // Brake pressure %
    } else if (type == "doors") {
        my_id = 0x03;              // Door ID
        simulated_value = 1.0f;    // 1 = Closed
    } else if (type == "lights") {
        my_id = 0x04;              // Lights ID
        simulated_value = 0.0f;    // 0 = Off
    } else {
        cout << "Unknown ECU type!" << endl;
        return 1;
    }

    try {
        UdpSocket ecu;
        VehicleMessage msg;
        msg.source_id = my_id;

        cout << "[" << type << " ECU] Online. Sending to Gateway..." << endl;

        while (true) {
            // 1. Send Heartbeat
            msg.type = MsgType::HEARTBEAT;
            msg.timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            ecu.SendTo("127.0.0.1", 8080, &msg, sizeof(msg));

            // 2. Send Data
            msg.type = MsgType::DATA;
            msg.payload = simulated_value;
            ecu.SendTo("127.0.0.1", 8080, &msg, sizeof(msg));

            // Randomize data
            if (type == "engine") simulated_value += (rand() % 10 - 5); 

            this_thread::sleep_for(chrono::seconds(1));
        }
    } catch (const exception& e) {
        cerr << "ECU Error: " << e.what() << endl;
    }

    return 0;
}