#include "header.h" 

bool isAbortFrame(String frame)
{
    frame.trim();
    if (!frame.startsWith("$,") || !frame.endsWith(",#"))
    {
        return false;
    }

    frame = frame.substring(2, frame.length() - 2);
    int commaIndex = frame.indexOf(',');
    if (commaIndex == -1)
    {
        return false;
    }

    String cmd = frame.substring(0, commaIndex);
    cmd.toUpperCase();

    return cmd == "ABORT";
}

void serviceAbortCommand()
{
    static char abortFrame[32];
    static uint8_t abortIndex = 0;

    if (!testrunning)
    {
        return;
    }

    while (Serial.available())
    {
        char c = Serial.read();

        if (c == '\r' || c == '\n')
        {
            continue;
        }

        if (abortIndex < sizeof(abortFrame) - 1)
        {
            abortFrame[abortIndex++] = c;
        }
        else
        {
            abortIndex = 0;
        }

        if (c == '#')
        {
            abortFrame[abortIndex] = '\0';

            if (isAbortFrame(String(abortFrame)))
            {
                abortrequested = true;
            }

            abortIndex = 0;
        }
    }
}

bool cooperativeDelay(unsigned long durationMs)
{
    unsigned long start = millis();

    while (millis() - start < durationMs)
    {
        serviceAbortCommand();

        if (abortrequested)
        {
            if (!abortresponsesent)
            {
                Serial.print("$,ABORTED,");
                Serial.print(currenttestname);
                Serial.println(",#");
                abortresponsesent = true;
            }
            return true;
        }

        delay(5);
    }

    return false;
}

void beginTestExecution()
{
    abortrequested = false;
    abortresponsesent = false;
    testrunning = true;
}

void endTestExecution()
{
    testrunning = false;
    currenttestname = "NONE";
}

void setCurrentTest(const char* testName)
{
    currenttestname = testName;
}

void runTest(const char* testName, void (*testFunction)())
{
    beginTestExecution();
    setCurrentTest(testName);
    testFunction();
    endTestExecution();
}
void sendSummary()
{
    Serial.print("$,SUMMARY");
    for (int idx = 0; idx < TEST_COUNT; idx++)
    {
        int statusCode = 0;
        if (test_executed[idx])
        {
            statusCode = test_result[idx] ? 1 : 2;
        }

        Serial.print(",");
        Serial.print(statusCode);
    }
    Serial.println(",#");
}

void parseFrame(String frame ) 
{
    frame.trim();
    // ignore responce 
    if (!frame.startsWith("$") || frame.indexOf("PASS") != -1 || frame.indexOf("FAIL") != -1)
    {
        return;     // Skip outgoing frames 
    }

    // validate frame format 
    if (!frame.startsWith("$,") || !frame.endsWith(",#"))    
    {
        Serial.println("ERR: Invalid Command Format");
        return;
    }

    // Remove "$," from start and ",#" from end
    frame = frame.substring(2, frame.length() - 2);   // extract command frame between delimiters

    int commaIndex = frame.indexOf(',');   // find first comma position
    if (commaIndex == -1)
    {
        Serial.println("ERR: Missing value");
        return;
    }

    String cmd = frame.substring(0, commaIndex);   // extract periferal name
    String valStr = frame.substring(commaIndex + 1);  // extract value

    // Convert value to integer
    int val = valStr.toInt();

    if (val == 0 && valStr != "0")  // if conversion fails
    {
        Serial.print("$,");
        Serial.print(cmd);
        Serial.print(",");
        Serial.print(valStr);
        Serial.println(",WRONG COMMAND,#");
        return;
    }

    cmdhandler(cmd, val);
}

void cmdhandler(String cmd, int val)
{
    cmd.toUpperCase();

    if (cmd == "ABORT")
    {
        abortrequested = true;
        return;
    }

    abortrequested = false;
    abortresponsesent = false;

    if (mac_executed == 0)
    {
        runTest("MAC", mac_test);
        mac_executed = 1;
    }

    if (val != 1 && val != 2) 
    {
        Serial.print("$,");
        Serial.print(cmd);
        Serial.print(",");
        Serial.print(val);
        Serial.println(",WRONG COMMAND,#");
        return;
    }

    if (cmd == "WIFI")
        runTest("WIFI", wifi_test);
    else if (cmd == "RGB")
        runTest("RGB", rgb_test);
    else if (cmd == "PCF1")
        runTest("PCF1", pcf1_test);
    else if (cmd == "PCF2")
        runTest("PCF2", pcf2_test);
    else if (cmd == "INPUT")
        runTest("INPUT", input_test);
    else if (cmd == "OUTPUT")
        runTest("OUTPUT", output_test);
    else if (cmd == "MAC")
        runTest("MAC", mac_test);
    else if (cmd == "ETHERNET")
        runTest("ETHERNET", ethernet_test);
    else if (cmd == "MQTT")
        runTest("MQTT", mqtt_test);
    else if (cmd == "RTC")
        runTest("RTC", rtc_test);
    else if (cmd == "RESET")
        runTest("RESET", reset_test);
    else if(cmd=="SCANNER")
    runTest("SCANNER", scanner_test);
    else if(cmd=="RS232")
    runTest("RS232", rs232_test);
    else if(cmd=="RS485")
    runTest("RS485", rs485_test);
    else if(cmd=="UART2")
    runTest("UART2", uart2_test);
    else if(cmd=="FILESYSTEM")
    runTest("FILESYSTEM", filesystem_test);
    else if (cmd == "SUMMARY")
        sendSummary();
    else if (cmd == "ALL") 
    {
        Serial.println("Running All Tests");
        beginTestExecution();
        setCurrentTest("RGB");
        rgb_test();        CHECK_ABORT();
        setCurrentTest("WIFI");
        wifi_test();       CHECK_ABORT();
        setCurrentTest("MQTT");
        mqtt_test();       CHECK_ABORT();
        setCurrentTest("RTC");
        rtc_test();        CHECK_ABORT();
        setCurrentTest("ETHERNET");
        ethernet_test();   CHECK_ABORT();
        setCurrentTest("PCF1");
        pcf1_test();       CHECK_ABORT();
        setCurrentTest("PCF2");
        pcf2_test();       CHECK_ABORT();
        setCurrentTest("INPUT");
        input_test();      CHECK_ABORT();
        setCurrentTest("OUTPUT");
        output_test();     CHECK_ABORT();
        setCurrentTest("UART2");
        uart2_test();      CHECK_ABORT();
        setCurrentTest("RS232");
        rs232_test();      CHECK_ABORT();
        setCurrentTest("RS485");
        rs485_test();      CHECK_ABORT();   
        setCurrentTest("FILESYSTEM");
        filesystem_test(); CHECK_ABORT();
        setCurrentTest("RESET");
        reset_test();      CHECK_ABORT();
        endTestExecution();
    }
    else 
    {
        Serial.print("$,");
        Serial.print(cmd);
        Serial.print(",");
        Serial.print(val);
        Serial.println(",INVALID COMMAND,#");
    }
}

// serial receive isr 
void onSerialReceive() 
{
    while (Serial.available()) 
    {
        char c = Serial.read();

        if (!frameready && i < sizeof(frame) - 1) 
        {
            frame[i++] = c;

            if (c == '#') 
            {
                frame[i]='\0';
                frameready = true;      // set flag 
            }
        } 
        else
        {
            i = 0; // Reset if buffer fills without a '#'
        }
    }
}

void setup() 
{
    Serial.begin(SERIAL_BAUD);
    Serial.println("Welcome ESP32-S3 : Gateway BenchTest");
    Serial.println("Initializing peripherals...");
    delay(2000); 

    rgb_init();          // initialize RGB
    reset_test_init();   // initialize reset test

    Serial.println("Initialization complete. Awaiting commands...");
}

void loop() 
{
    onSerialReceive(); // poll serial input (USB CDC has no onReceive callback)

    if (frameready)
    {
        frameready = false;        // clear flag
        parseFrame(String((char*)frame));
        i=0;                    // reset index of buffer
        memset((void*)frame, 0, sizeof(frame));  // clear buffer 
    }
}
