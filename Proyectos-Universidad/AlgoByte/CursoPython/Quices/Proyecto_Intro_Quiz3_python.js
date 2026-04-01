const startingMinutes = 2;
let time = startingMinutes * 60;

const countdownEl = document.getElementById("timer");

setInterval(updateCountdown, 1000);

function updateCountdown() {
  const minutes = Math.floor(time/60);
  let seconds = time % 60;

  seconds = seconds < 10 ? '0' + seconds: seconds;

  countdownEl.innerHTML = `${minutes}:${seconds}`;



  time--;
  if(time === 0) {
    ganaPunto();
    countdownEl.style.display = "none";
  }
}

let answered = false;

let calificacion = 0;
function ganaPunto() {
    if(answered) {
        return;
    }

    let htmlElements = document.getElementsByTagName("input");
    for(let i = 0; i < htmlElements.length; i++) {
        var isChecked = htmlElements[i].checked;
        var isTrue = htmlElements[i].value;

        if(isTrue === "true" && isChecked) {
            calificacion += 0.5;
        } else if (isChecked) {
            calificacion -= 0.5;
        } 
    }

    if(calificacion < 0) {
        calificacion = 0;
    }

    var result = document.getElementById("result");
    result.textContent = `Has obtenido ${calificacion} de 7.5 respuestas correctas.`;

    answered = true;
    document.getElementById("timer").style.display = "none";
}
