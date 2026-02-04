import subprocess
import time
import os
import signal
import sys

ECU_TYPES = ["engine", "brakes", "doors", "lights"]
PROCESSES = []

def start_simulator():
    print("🚀 Starting Ford FNV Network Simulator...")
    
    gw_proc = subprocess.Popen(
        ["./build/gateway"], 
        stdout=subprocess.PIPE, 
        stderr=subprocess.STDOUT, 
        text=True,
        bufsize=1
    )
    PROCESSES.append(gw_proc)
    time.sleep(1)

    for ecu in ECU_TYPES:
        print(f"🔌 Launching {ecu.upper()} ECU...")
        p = subprocess.Popen(["./build/ecu_node", ecu], stdout=subprocess.DEVNULL)
        PROCESSES.append(p)
    
    return gw_proc

def reset_ecu(ecu_type):
    print(f"🔄 Manager triggering RESET for {ecu_type}...")
    for p in PROCESSES:
        if len(p.args) > 1 and p.args[1] == ecu_type:
            p.kill()
            p.wait()
            PROCESSES.remove(p)
            break
    
    new_p = subprocess.Popen(["./build/ecu_node", ecu_type], stdout=subprocess.DEVNULL)
    PROCESSES.append(new_p)
    print(f"✅ {ecu_type.upper()} ECU has been restarted.")

def cleanup(sig, frame):
    print("\n🛑 Shutting down vehicle network...")
    for p in PROCESSES:
        p.terminate()
    exit(0)

if __name__ == "__main__":
    signal.signal(signal.SIGINT, cleanup)
    
    if not os.path.exists("./build/gateway") or not os.path.exists("./build/ecu_node"):
        print("❌ Error: Run 'make' in build folder first.")
        sys.exit(1)

    # 1. Start the system
    gw = start_simulator()

    # 2. Test Failure: Kill engine after 10 seconds
    print("\n⏳ System running. Waiting 10s before injecting fault...")
    time.sleep(10)
    print("\n🔥 FAULT INJECTION: Killing Engine ECU process...")
    for p in PROCESSES:
        if len(p.args) > 1 and p.args[1] == "engine":
            p.kill()
            p.wait()
            break

    # 3. Monitor Loop: Read Gateway output for ALERTS
    try:
        while True:
            line = gw.stdout.readline()
            if line:
                print(line.strip()) # Show the gateway output
                
                if "ALERT: ECU [1]" in line:
                    reset_ecu("engine")
            
            # Check if gateway process died
            if gw.poll() is not None:
                break
    except KeyboardInterrupt:
        cleanup(None, None)