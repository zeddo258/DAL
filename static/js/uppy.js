import { Uppy, Dashboard, XHRUpload } from "https://releases.transloadit.com/uppy/v3.17.0/uppy.min.mjs"

const uppy = new Uppy({
    autoProceed: false,
    restrictions: {
        allowedFileTypes: ['.cpp'] // 只允許 .cpp 檔案
    }
});

uppy.use(Dashboard, {
    target: '#drag-drop-area',
    inline: true,
    disableInformer: true,  // 禁用訊息提示
    disableStatusBar: true  // 禁用狀態欄
});

uppy.use(XHRUpload, {
    endpoint: '/upload',
    timeout: 500  // 設置為 5 秒
});


// 當有檔案或資料夾被添加時觸發
uppy.on('files-added', (files) => {
    files.forEach(file => {
        if (file.type === 'folder') {
            // 假設 folder.files 是資料夾內的檔案陣列
            file.folder.files.forEach(innerFile => {
                if (innerFile.extension === 'cpp') {
                    // 添加這個 .cpp 檔案到 Uppy 實例
                    uppy.addFile({
                        name: innerFile.name,
                        type: innerFile.type,
                        data: innerFile.data,
                        source: 'Local', // 或其他來源
                    });
                }
            });
        }
    });
});


uppy.on('upload-error', (file, error, response) => {
    console.log('Error with file:', file.id);
    uppy.retryAll()  // 手動重試所有失敗的上傳
  })

document.addEventListener("DOMContentLoaded", function() {
    const submitBtn = document.querySelector(".post-btn");
    submitBtn.addEventListener("click", function() {
        const homeworkMenu = document.querySelector("#homework .sBtn-text").innerText;
        const typeMenu = document.querySelector("#type .sBtn-text").innerText;

        const postData = {
            homework: homeworkMenu,
            type: typeMenu
        };

        uppy.upload();  // 手動觸發 Uppy 的上傳

    
        fetch("/upload", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(postData)
        })

        .then(data => {
            console.log("Success:", data);
        })
        .catch((error) => {
            console.error("Error:", error);
        });
    });
});
