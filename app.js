const express = require('express');
const addon = require('./build/Release/addon.node');

const app = express();
const port = 3000;

app.use(express.static('public'));
app.use(express.json());

app.post('/check', (req, res) => {
  const username = req.body.username;
  const privilege = addon.checkPrivilege(username);
  res.json({ username, privilege });
});

app.listen(port, () => console.log(`Server running on port ${port}`));
