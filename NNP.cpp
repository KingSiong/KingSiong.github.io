/*

Author: KingSiong
Date: 07/23/2022

*/
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1007;
string title, source;

string NNP_template() {
    string res = "";
    res = res + "title: " + title + "\n";
    res = res + "source: " + source + "\n";
    res = res + "author:\n";
    res = res + "remark:\n";
    return res;
}

int string2int(string str) {
    int res = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] >= '0' && str[i] <= '9') res = res * 10 + str[i] - '0';
        if (str[i] == '\n' || str[i] == '\r' || str[i] == 0) break;
    }
    return res;
}

string int2string(int num) {
    string res = "";
    if (!num) return "0";
    while (num) {
        char digit = (num % 10) + '0';
        res = digit + res;
        num /= 10;
    }
    return res;
}

void NNP_new(string title) {
    string cmd = "touch " + title + ".md && touch " + source + ".cpp";
    system(cmd.c_str());
    ofstream OUT("./" + title + ".md");
    OUT << NNP_template();
}

void NNP_submit(string title) {
    string cmd = "mv " + source + ".cpp ./SourceCode/" + source + ".html";
    system(cmd.c_str());
    cmd = "python add_record.py " + title + " " + source;
    system(cmd.c_str());
    cmd = "rm -f " + title + ".md";
    system(cmd.c_str());
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        string cmd = argv[1];
        title = argv[2];
        FILE *fp = popen("find SourceCode -type f | wc -l", "r");
        char buffer[MAX_N];
        fread(buffer, 1, sizeof(buffer), fp);
        int cnt = string2int(buffer);
        pclose(fp);
        source = int2string(cnt) + "_" + title;
        if (cmd == "new" || cmd == "n") {
            if (argc > 2) {
                NNP_new(title);
                cout << title + ".md has been created.\n";
            }
        } else if (cmd == "submit" || cmd == "s") {
            if (argc > 2) {
                NNP_submit(title);
                cout << title + ".md has been submitted.\n";
            }
        }
    }
    return 0;
}