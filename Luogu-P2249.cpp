//
// Created by Linza on 2026/9/22.
//
#include<cstdio>
#include<vector>

using namespace std;

class FastIO {
private:
    static const int BUF_SIZE = 1 << 20;
    static char inputBuffer[BUF_SIZE];
    static char outputBuffer[BUF_SIZE];
    int inputPos = 0;
    int inputLength = 0;
    int outputPos = 0;

    char getChar() {
        if (inputPos >= inputLength) {
            inputLength = static_cast<int>(fread(inputBuffer, 1, BUF_SIZE, stdin));
            inputPos = 0;
            if (inputLength == 0) {
                return 0;
            }
        }
        return inputBuffer[inputPos++];
    }

public:
    int readInt() {
        char c = getChar();
        while (c <= ' ' && c != 0) {
            c = getChar();
        }

        int sign = 1;
        if (c == '-') {
            sign = -1;
            c = getChar();
        }

        int value = 0;
        while (c >= '0' && c <= '9') {
            value = value * 10 + (c - '0');
            c = getChar();
        }
        return value * sign;
    }

    void writeChar(char c) {
        if (outputPos == BUF_SIZE) {
            flush();
        }
        outputBuffer[outputPos++] = c;
    }

    void writeInt(int value) {
        if (value == 0) {
            writeChar('0');
            return;
        }
        if (value < 0) {
            writeChar('-');
            value = -value;
        }

        char number[12];
        int length = 0;
        while (value > 0) {
            number[length++] = static_cast<char>('0' + value % 10);
            value /= 10;
        }
        while (length > 0) {
            writeChar(number[--length]);
        }
    }

    void flush() {
        if (outputPos > 0) {
            fwrite(outputBuffer, 1, outputPos, stdout);
            outputPos = 0;
        }
    }

    ~FastIO() {
        flush();
    }
};

char FastIO::inputBuffer[FastIO::BUF_SIZE];
char FastIO::outputBuffer[FastIO::BUF_SIZE];

int main() {
    FastIO io;
    int n,m;
    n = io.readInt();
    m = io.readInt();
    vector<int> a(n,0);
    for (int i = 0; i < n; i++) {
        a[i] = io.readInt();
    }


    for (int i = 0; i < m; i++) {
        int cmp;
        int left = 0;
        int right = n - 1;
        bool found = false;
        cmp = io.readInt();
        while (left <= right) {
            int mid = left+ (-left + right) / 2;
            if (a[mid] < cmp) {
                left = mid + 1;
            }
            if (a[mid] >= cmp) {
                if (a[mid] == cmp) {
                    found = true;
                }
                right = mid - 1;
            }

        }
        int mid = (left+ (-left + right) / 2) + 1;
        if (found) {
            io.writeInt(mid);
            io.writeChar(' ');
        }
        else {
            io.writeInt(-1);
            io.writeChar(' ');
        }
    }
}
