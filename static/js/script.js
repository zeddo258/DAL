// 函數用於為選項添加點擊事件
function addClickEventToOptions(optionMenu) {
    const options = optionMenu.querySelectorAll(".option");
    const sBtn_text = optionMenu.querySelector(".sBtn-text");

    // 為每個選項添加點擊事件
    options.forEach(option => {
        option.addEventListener("click", () => {
            let selectedOption = option.querySelector(".option-text").innerText;
            sBtn_text.innerText = selectedOption;
            optionMenu.classList.remove("active");
        });
    });
}

fetch('/hw_list')  // 請求 Django API
.then(response => response.json())
.then(data => {
    const ulElement = document.getElementById('homeworkOptions');

    data.forEach(item => {
        const li = document.createElement('li');
        li.className = 'option';

        const span = document.createElement('span');
        span.className = 'option-text';
        span.textContent = item;

        li.appendChild(span);
        ulElement.appendChild(li);
    });

    // 添加事件監聽器到新添加的選項
    addClickEventToOptions(ulElement.closest('.select-menu'));
});

// 選擇所有的 .select-menu 元素
const optionMenus = document.querySelectorAll(".select-menu");

// 為每個選單添加事件監聽器
optionMenus.forEach(optionMenu => {
    const selectBtn = optionMenu.querySelector(".select-btn");

    // 當點擊 selectBtn 時，切換選單的 active 狀態
    selectBtn.addEventListener("click", () => optionMenu.classList.toggle("active"));

    addClickEventToOptions(optionMenu);
});


// 獲取 homework 和 post-btn 元素
const homework = document.getElementById("hw");
const postBtn = document.querySelector(".post-btn");

// 函數用於檢查被選中的選項並更新 post-btn 的透明度
function updatePostBtnOpacity() {
    
    if (homework.textContent === "Select Homework") {
        postBtn.style.opacity = "0";
    } else {
        postBtn.style.opacity = "1";
    }
    
}

// 創建一個 Mutation Observer 實例來監聽 DOM 變化
const observer = new MutationObserver(() => {
    updatePostBtnOpacity();
});

// 配置觀察選項：
const config = { attributes: true, childList: true, subtree: true };

// 開始監聽 homework 元素及其子元素的變化
observer.observe(homework, config);

// 初始設置
updatePostBtnOpacity();