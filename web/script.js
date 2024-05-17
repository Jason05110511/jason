//-----------長蘑菇--------------------
var a = 1;
var maxImages = 800; // 設置最多允許的圖片數量
var scrollDistance = 40; // 設置滾動距離的閾值

function getRndInt(min, max) {
    return Math.floor(Math.random() * (max - min)) + min;
}

function add() {
    let tt = getRndInt(57, 93);
    let rr = getRndInt(0, 95);

    let demo = document.getElementById("demo");
    let images = demo.querySelectorAll('.mush');

    // 檢查當前圖片數量是否小於最大允許數量
    if (images.length < maxImages) {
        let newMushroom = document.createElement('img');
        newMushroom.classList.add('mush');
        newMushroom.src = "./images/mushroom5.png";
        newMushroom.style.top = tt + '%';
        newMushroom.style.right = rr + '%';

        // 點擊事件
        newMushroom.addEventListener('click', function () {
            // 在點擊時執行爆炸效果
            this.style.transition = 'transform 0.3s ease-in-out';
            this.style.transform = 'scale(0)';

            // 等待爆炸效果完成後移除元素
            setTimeout(() => {
                demo.removeChild(newMushroom);
            }, 300);
        });

        demo.appendChild(newMushroom);
    }
}

function remove() {
    let demo = document.getElementById("demo");
    let images = demo.querySelectorAll('.mush');

    // 移除最晚添加的圖片
    let lastImageIndex = images.length - 1;
    if (lastImageIndex >= 0) {
        demo.removeChild(images[lastImageIndex]);
    }
}

let lastScrollTop = 0;
let scrolledDistance = 0;

window.addEventListener("scroll", function () {
    let st = window.pageYOffset || document.documentElement.scrollTop;

    // 計算滾動距離
    let scrollDelta = st - lastScrollTop;
    scrolledDistance += Math.abs(scrollDelta);

    if (st === 0) {
        remove();
    }

    // 判斷是否滾動超過閾值
    if (scrolledDistance >= scrollDistance) {
        // 重置滾動距離
        scrolledDistance = 0;

        // 判斷滾輪的滑動方向
        if (scrollDelta > 0) {
            // 下滑，新增圖片
            add();
        } else {
            // 上滑，刪除圖片
            remove();
        }
    }

    lastScrollTop = st;
});
//----------------rr r1-------------
let rrOriginalp;
document.addEventListener('DOMContentLoaded', function () {
    rrOriginalp = parseInt(getComputedStyle(document.querySelector('.box.rr.r1')).left) || 0;
});
window.addEventListener('scroll', function () {
    var box = document.querySelector('.box.rr');
    var scrollY = window.scrollY;
    //console.log(box.style.left);
    // 根據滾動的垂直位置動態更新 .box 的 left 屬性
    //box.style.left = (rrOriginalp + (scrollY * 0.5)) + 'px';
    //根據滾動的垂直位置動態更新 .box 的位置，使用 transform
    box.style.transform = 'translateX(' + (rrOriginalp - (scrollY * 0.85)) + 'px)';
});
//--------------------LL L1-------------
let llOriginalp;
document.addEventListener('DOMContentLoaded', function () {
    llOriginalp = parseInt(getComputedStyle(document.querySelector('.box.ll.l1')).left) || 0;
});
window.addEventListener('scroll', function () {
    var box = document.querySelector('.box.ll');
    var scrollY = window.scrollY;
    box.style.transform = 'translateX(' + (llOriginalp + (scrollY * 0.85)) + 'px)';
});
//-----------btn---------------
/*
document.getElementById('btn1').addEventListener('click', function () {
    document.getElementById('inputContainer').style.display = 'block';
  });*/
  
  function btn1() {
    if(window.getComputedStyle(inputContainer).display === 'none') {
        document.getElementById('inputContainer').style.display = 'block';
    }
    else{
        document.getElementById('inputContainer').style.display = 'none';
    }
  };
  function submit() {
    var userInput = document.getElementById('textInput').value;
    document.getElementById('pp1').innerText += userInput;
    document.getElementById('inputContainer').style.display = 'none';
  }
  //--------------------------------
//   isNone(e){
//     // 阻止事件冒泡
//     e.stopPropagation();
  
//     // 获取元素引用
//     const boxElement = this.$refs["box"];
  
//     // 取反 none 的状态
//     this.none = !this.none;
  
//     // 根据 none 的状态切换元素的显示与隐藏
//     if (this.none) {
//       // 如果 none 为 true，设置定时器延迟隐藏
//       clearTimeout(this.time);
//       this.time = setTimeout(() => {
//         boxElement.style.display = "none";
//       }, 500);
//     } else {
//       // 如果 none 为 false，立即显示元素
//       clearTimeout(this.time);
//       boxElement.style.display = "block";
//     }
//   };
//-----------------------------------
// function isElementCovered(element) {
//     if (!(element instanceof Element)) {
//         console.error('Invalid element passed to isElementCovered');
//         return false;
//     }

//     var computedStyle = getComputedStyle(element);

//     // 獲取元素的 z-index 和 position 屬性
//     var zIndex = parseInt(computedStyle.zIndex, 10);
//     var position = computedStyle.position;

//     // 如果 z-index 是 NaN 或 position 是 static，說明元素沒有被定位
//     if (isNaN(zIndex) || position === 'static') {
//         return false;
//     }

//     // 獲取元素的位置信息
//     var rect = element.getBoundingClientRect();
//     var elementsBelow = document.elementsFromPoint(rect.x + rect.width / 2, rect.y + rect.height / 2);

//     // 檢查是否有其他元素的 z-index 大於當前元素
//     for (var i = 0; i < elementsBelow.length; i++) {
//         var elementBelow = elementsBelow[i];
//         var zIndexBelow = parseInt(getComputedStyle(elementBelow).zIndex, 10);

//         if (!isNaN(zIndexBelow) && zIndexBelow > zIndex) {
//             return true;
//         }
//     }

//     return false;
// }

// // 使用示例
// var g1Element = document.querySelector('.glass.g1');
// if (g1Element) {
//     if (isElementCovered(g1Element)) {
//         console.log('g1 is covered');
//     } else {
//         console.log('g1 is not covered');
//     }
// } else {
//     console.error('Could not find .glass .g1 element');
// }


  