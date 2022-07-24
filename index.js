/*

Author: KingSiong
Date: 07/23/2022

*/

function NNPDisplay(content) {
    document.write(content);
}

function NNPDisplayWithID(content, id) {
    document.getElementById(id).innerHTML = content;
}

async function NNPDisplayWithFile(file, id) {
    let obj = await fetch(file);
    let text = await obj.text();
    NNPDisplayWithID(text, id);
}

async function NNPFetchJSONObj(file) {
    let obj = await fetch(file);
    let text = await obj.text();
    return JSON.parse(text);
}

function NNPGetContent(obj) {
    let content = "";
    content = content + "<p>";
    content = content + "Title: " + obj["title"] + "<br>";
    content = content + "Date: " + obj["time"] + "<br>";
    content = content + "Author: " + obj["author"] + "<br>";
    content = content + "Remark: " + obj["remark"] + "<br>";
    content = content + "<a href = /Code/" + obj["source"] + ">Code Link</a>";
    content = content + "</p>";
    return content;
}

async function NNPContentShow(id) {
    let JSONObj = await NNPFetchJSONObj("./record.json");
    let JSONObjSize = Object.keys(JSONObj["record"]).length;
    console.log(JSONObjSize)
    let content = "";
    for (i = JSONObjSize - 1; i >= 0; --i) {
        console.log(JSONObj["record"][i]["source"]);
        content = content + NNPGetContent(JSONObj["record"][i]);
    }
    NNPDisplayWithID(content, id)
}