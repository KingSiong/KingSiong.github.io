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

string lineCodeToHtml(string s) {
    string res = "";
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '<') {
            res += "&lt;";
        } else if (s[i] == '>') {
            res += "&gt;";
        } else {
            res += s[i];
        }
    }
    return res;
}

string cppToHtml(string file) {
    ifstream IN(file);
    string res = 
"<!DOCTYPE html>\n\
<html>\n\
    <head>\n\
        <link rel=\"stylesheet\" href=\"../default.min.css\">\n\
        <script src=\"../highlight.min.js\"></script>\n\
        <script src=\"../highlightjs-line-numbers.min.js\"></script>\n\
        <script>\n\
            hljs.initHighlightingOnLoad();\n\
            hljs.initLineNumbersOnLoad();\n\
        </script>\n\
        <style>\n\
            .hljs-ln-numbers {\n\
                text-align: center;\n\
                color: #ccc;\n\
                border-right: 1px solid #999;\n\
                vertical-align: top;\n\
                padding-right: 5px;\n\
                -webkit-touch-callout: none;\n\
                -webkit-user-select: none;\n\
                -khtml-user-select: none;\n\
                -moz-user-select: none;\n\
                -ms-user-select: none;\n\
                user-select: none;\n\
            }\n\
        </style>\n\
        <title>NNP's Repo</title>\n\
    </head>\n";
    res = res + "<body>\n";
    res = res + "<pre><code>";
    char buffer[MAX_N];
    while (IN.getline(buffer, MAX_N)) {
        res += lineCodeToHtml(buffer);
        res += "\n";
    }
    res = res + "</pre></code>\n";
    res = res + "</body>\n";
    res = res + "</html>\n";
    IN.close();
    return res;
}

void NNP_new(string title) {
    string cmd = "mkdir " + source + "/";
    cmd = cmd + " && " + "touch ./" + source + "/" + title + ".md";
    cmd = cmd + " && " + "touch ./" + source + "/source_code.cpp";
    system(cmd.c_str());
    ofstream OUT("./" + source + "/" + title + ".md");
    OUT << NNP_template();
}

void NNP_submit(string title) {
    string html = cppToHtml("./" + source + "/source_code.cpp");
    string cmd = "touch ./" + source + "/index.html";
    system(cmd.c_str());
    ofstream OUT("./" + source + "/index.html");
    OUT << html;
    OUT.close();
    cmd = "python add_record.py " + title + " " + source;
    system(cmd.c_str());
    cmd = "mv ./" + source + "/" + " ./Code/" + source; 
    system(cmd.c_str());

}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        string cmd = argv[1];
        title = argv[2];
        FILE *fp = popen("find Code -type d | wc -l", "r");
        char buffer[MAX_N];
        fread(buffer, 1, sizeof(buffer), fp);
        int cnt = string2int(buffer) - 1;
        pclose(fp);
        source = int2string(cnt) + "_" + title;
        if (cmd == "new" || cmd == "n") {
            if (argc > 2) {
                NNP_new(title);
                cout << title + "/ has been created on " + source + "/.\n";
            }
        } else if (cmd == "submit" || cmd == "s") {
            if (argc > 2) {
                NNP_submit(title);
                cout << source + "/ has been submitted.\n";
            }
        }
    }
    return 0;
}