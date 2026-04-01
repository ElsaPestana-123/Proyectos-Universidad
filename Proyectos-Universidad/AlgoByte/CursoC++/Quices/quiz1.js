const startingMinutes = 1;
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
    submitQuiz();
    countdownEl.style.display = "none";
  }
}

let answered = false;

function submitQuiz() {
    if(answered) {
        return;
    }
    // Respuestas correctas
    var correctAnswers = {
        q1: "true",
        q2: "true",
        q3: "false",
        q4: "true",
        q5: "false",
        q6: "true",
        q7: "false",
        q8: "true",
        q9: "false",
        q10: "true"
    };

    // Contador de respuestas correctas
    var correct = 0;

    // Iterar sobre las respuestas correctas y comparar con las seleccionadas
    for (var q in correctAnswers) {
        var answer = document.querySelector(`input[name="${q}"]:checked`);
        if (answer && answer.value === correctAnswers[q]) {
            correct++;
        }
    }

    // Mostrar el resultado
    var result = document.getElementById("result");
    result.textContent = `Has obtenido ${correct} de 10 respuestas correctas.`;
    answered = true;

    document.getElementById("timer").style.display = "none";
}
