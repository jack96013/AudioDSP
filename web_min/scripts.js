document.getElementById('toggleBtn').addEventListener('click', function() {
    const sidebar = document.getElementById('sidebar');
    sidebar.classList.toggle('collapsed');
});

document.querySelectorAll('.slider').forEach(slider => {
    slider.addEventListener('input', function() {
        console.log(`${this.id}: ${this.value}`);
        // 在這裡添加對等化器音量變化的控制代碼
    });
});