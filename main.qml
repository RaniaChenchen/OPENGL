

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import OpenGLRenderer 1.0
import DatabaseHandler 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("OpenGL & MySQL CRUD App")

    // // Intégration de OpenGLRenderer dans le QML
    // OpenGLRenderer {
    //     anchors.fill: parent
    // }


    Rectangle {
        width: parent.width
        height: 100
        anchors.bottom: parent.bottom
        color: "#f0f0f0"
        Row {
            anchors.centerIn: parent
            spacing: 20

            Button {
                text: "Read Users"
                onClicked: {
                    readUsers();  // Lire les utilisateurs depuis la base de données
                }
            }

            Button {
                text: "Add User"
                onClicked: {
                    var id = Math.floor(Math.random() * 1000);  // Id généré aléatoirement
                    var name = "New User";
                    insertUser(id, name);  // Ajouter un utilisateur avec un id et un nom
                }
            }

            Button {
                text: "Apple Update"
                onClicked: {
                    console.log("Apple Update clicked");
                }
            }

            Button {
                text: "Apple Delete"
                onClicked: {
                    console.log("Apple Delete clicked");
                }
            }
        }
    }

    // Fonction pour lire les utilisateurs depuis la base de données
    function readUsers() {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "http://localhost/cud/apiget.php?action=read", true);
        xhr.onload = function() {
            if (xhr.status === 200) {
                var jsonResponse = JSON.parse(xhr.responseText);
                var buttonContainer = Qt.createQmlObject('import QtQuick 2.15; Column { width: parent.width; spacing: 10 }', userListView);
                jsonResponse.forEach(function(user) {
                    createUserButtons(user.id, user.name, buttonContainer);
                });
            } else {
                console.error("Error reading users");
            }
        };
        xhr.send();
    }

    // Fonction pour insérer un nouvel utilisateur
    function insertUser(id, name) {
        var xhr = new XMLHttpRequest();
        var url = "http://localhost/crud/apiget.php?action=insert&id=" + encodeURIComponent(id) +
                  "&name=" + encodeURIComponent(name);
        xhr.open("GET", url, true);
        xhr.onload = function() {
            if (xhr.status === 200) {
                console.log("User inserted successfully");
                readUsers();  // Rafraîchir la liste des utilisateurs après l'insertion
            } else {
                console.error("Error inserting user");
            }
        };
        xhr.send();
    }

    function deleteUser(id) {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "http://localhost/crud/apiget.php?action=delete&id=" + id, true);
        xhr.onload = function() {
            if (xhr.status === 200) {
                console.log("User deleted successfully");
                readUsers();  // Rafraîchir la liste après la suppression
            } else {
                console.error("Error deleting user");
            }
        };
        xhr.send();
    }

    function updateUser(id, name) {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "http://localhost/crud/apiget.php?action=update&id=" + id + "&name=" + encodeURIComponent(name), true);
        xhr.onload = function() {
            if (xhr.status === 200) {
                console.log("User updated successfully");
                readUsers();  // Rafraîchir la liste après la mise à jour
            } else {
                console.error("Error updating user");
            }
        };
        xhr.send();
    }

    function createUserButtons(id, name, parent) {
        var userButtons = Qt.createQmlObject('import QtQuick 2.15; Item { width: parent.width; height: 50; Row { spacing: 10; width: parent.width; Text { text: "' + name + '"; width: parent.width * 0.6; anchors.verticalCenter: parent.verticalCenter } Button { text: "Delete"; anchors.verticalCenter: parent.verticalCenter; onClicked: { deleteUser(' + id + ') } } Button { text: "Update"; anchors.verticalCenter: parent.verticalCenter; onClicked: { var newName = prompt("Enter new name", "' + name + '"); if (newName) { updateUser(' + id + ', newName); } } } } }', parent);
    }

    Component.onCompleted: {
        readUsers();  // Charger les utilisateurs au démarrage de l'application
    }
}

