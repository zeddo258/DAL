from bs4 import BeautifulSoup

# 檔案列表和對應的狀態
file_list = [
    {"name": "檔案1", "status": "Success", "link": "#", "upload_seq": "123", "topic": "topic1", "unit": "unit1"},
    {"name": "檔案2", "status": "Runtime_Error", "link": "#", "upload_seq": "456", "topic": "topic2", "unit": "unit2"},
    {"name": "檔案3", "status": "Compile_Error", "link": "#", "upload_seq": "789", "topic": "topic3", "unit": "unit3"},
]


def make_report_html(file_list, path):
    # 讀取 HTML 模板
    with open("/home/ds/DAL/templates/template.html", "r", encoding="utf-8") as f:
        template_content = f.read()

    # 使用 BeautifulSoup 解析 HTML
    soup = BeautifulSoup(template_content, 'html.parser')

    # 找到要插入項目的地方
    dynamic_list = soup.find(id="dynamicList")
    script_tags = []
    for index, file in enumerate(file_list, 1):
        download_id = f"download_{index}"
        
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


        download_icon = soup.new_tag("i", **{"class": "fa-solid fa-download", "id": download_id})

        # 將 "download" 圖標添加到檔案名旁邊
        file_element.append(download_icon)

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
        
        # 更新 <script> 標籤的內容
        script_content = f'''
        document.addEventListener('DOMContentLoaded', function() {{
            const downloadLink = document.getElementById('{download_id}');
            downloadLink.addEventListener('click', function(event) {{
                event.preventDefault();
                event.stopPropagation();
                
                const get_code = {{
                    upload_seq: '{file['upload_seq']}',
                    topic: '{file['topic']}',
                    unit: '{file['unit']}',
                    target_file_name: '{file['name']}'
                }};
                
                fetch('/get_code', {{
                    method: 'POST',
                    headers: {{
                        'Content-Type': 'application/json'
                    }},
                    body: JSON.stringify(get_code)
                }})
                    
                .then(response => response.blob())
                .then(blob => {{
                    const url = window.URL.createObjectURL(blob);
                    const a = document.createElement('a');
                    a.style.display = 'none';
                    a.href = url;
                    a.download = '{file['name']}.zip';
                    document.body.appendChild(a);
                    a.click();
                    window.URL.revokeObjectURL(url);
                }})
                .catch((error) => {{
                    console.error('Error:', error);
                }});
            }});
        }});
        '''

        
        script_tag = soup.new_tag('script')
        script_tag.string = script_content
        script_tags.append(script_tag)
        
    # 將 script 標籤添加到 head
    head = soup.find('head')
    for script_tag in script_tags:
        head.append(script_tag)
        
    # 將修改後的 HTML 內容保存到新的文件中
    with open(path, "w", encoding="utf-8") as f:
        f.write(str(soup))


if __name__ == '__main__':
    make_report_html(file_list, "/home/ds/DAL/test_report.html")