document.getElementById('userForm').addEventListener('submit', function(e) {
    e.preventDefault();
    const username = document.getElementById('username').value;

    fetch('/check', {
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify({username})
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById('result').textContent = `Пользователь ${data.username} имеет привелегию ${data.privilege}`;
    });
});
