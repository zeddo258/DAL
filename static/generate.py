from bs4 import BeautifulSoup

# 檔案列表和對應的狀態
file_list = [
    {"name": "檔案1", "status": "success"},
    {"name": "檔案2", "status": "error"},
    {"name": "檔案3", "status": "infinite-loop"}
]

# 讀取 HTML 模板
with open("template.html", "r", encoding="utf-8") as f:
    template_content = f.read()

# 使用 BeautifulSoup 解析 HTML
soup = BeautifulSoup(template_content, 'html.parser')

# 找到要插入項目的地方
dynamic_list = soup.find(id="dynamicList")

# 動態生成每一個檔案的 HTML 內容
for file in file_list:
    new_item = soup.new_tag("li", **{"class": "list-item"})
    
    file_element = soup.new_tag("span", **{"class": "file"})
    file_element.string = file["name"]
    
    status_element = soup.new_tag("span", **{"class": f"status {file['status']}"})
    status_element.string = f"狀態：{file['status'].replace('-', ' ')}"
    
    new_item.append(file_element)
    new_item.append(status_element)
    
    dynamic_list.append(new_item)

# 將修改後的 HTML 內容保存到新的文件中
with open("dynamic_list.html", "w", encoding="utf-8") as f:
    f.write(str(soup))