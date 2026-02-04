#include <iostream>
#include <map>
#include <chrono>
#include <vector>
#include "common/Protocol.h"
#include "common/UdpSocket.h"

using namespace std;
using namespace std::chrono;

// Structure to track the status of each ECU
struct EcuStatus {
    steady_clock::time_point last_seen;
    bool is_online;
};

int main() {
    try {
        UdpSocket gateway;
        gateway.Bind(8080);
        
        // The Node Management Table
        map<uint32_t, EcuStatus> node_table;
        
        VehicleMessage msg;
        cout << "[Gateway] Monitoring Network Health..." << endl;

        while (true) {
            // 1. Receive data (Non-blocking or with a timeout is better, 
            // but for this sim, we'll process after every packet)
            int bytes = gateway.Recv(&msg, sizeof(msg));

            if (bytes == sizeof(VehicleMessage)) {
                // Update the table for this ECU
                node_table[msg.source_id] = {steady_clock::now(), true};

                if (msg.type == MsgType::DATA) {
                    cout << "[ID: " << msg.source_id << "] Data: " << msg.payload << endl;
                }
            }

            // 2. Health Check: Iterate through all known ECUs
            auto now = steady_clock::now();
            for (auto& [id, status] : node_table) {
                auto elapsed = duration_cast<seconds>(now - status.last_seen).count();

                if (elapsed > 3 && status.is_online) {
                    cout << "🛑 ALERT: ECU [" << id << "] TIMEOUT! Last seen " 
                         << elapsed << "s ago." << endl;
                    status.is_online = false; // Mark offline so we don't spam alerts
                }
            }
        }
    } catch (const exception& e) {
        cerr << "Gateway Error: " << e.what() << endl;
    }
    return 0;
}