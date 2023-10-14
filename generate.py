from bs4 import BeautifulSoup

# 檔案列表和對應的狀態
file_list = [
    {"name": "檔案1", "status": "Success", "link": "https://www.google.com"},
    {"name": "檔案2", "status": "Runtime_Error", "link": "https://www.google.com"},
    {"name": "檔案3", "status": "Compile_Error", "link": "https://www.google.com"}
]


def make_report_html(file_list, path):
    # 讀取 HTML 模板
    with open("/home/ds/DAL/templates/template.html", "r", encoding="utf-8") as f:
        template_content = f.read()

    # 使用 BeautifulSoup 解析 HTML
    soup = BeautifulSoup(template_content, 'html.parser')

    # 找到要插入項目的地方
    dynamic_list = soup.find(id="dynamicList")

    for file in file_list:
        # 創建新的 li 標籤
        new_item = soup.new_tag("li", **{"class": "list-item"})

        # 創建新的 a 標籤並設定 href 屬性
        if file['link'] is None:
            link_element = soup.new_tag("p")
        else:
            link_element = soup.new_tag("a", **{"href": f"/{file['link']}"})

        # 創建新的 span 標籤用於顯示檔案名
        file_element = soup.new_tag("span", **{"class": "file"})
        file_element.string = file["name"]

        # 創建新的 span 標籤用於顯示狀態
        status_element = soup.new_tag("span", **{"class": f"status {file['status']}"})
        status_element.string = file['status']

        # 將 span 標籤添加到 a 標籤內
        link_element.append(file_element)
        link_element.append(status_element)

        # 將 a 標籤添加到 li 標籤內
        new_item.append(link_element)

        # 將 li 標籤添加到 ul 標籤內
        dynamic_list.append(new_item)

    # 將修改後的 HTML 內容保存到新的文件中
    with open(path, "w", encoding="utf-8") as f:
        f.write(str(soup))
