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
    showScore();
    countdownEl.style.display = "none";
  }
}



var currentquestion = 0;
const questions = [{
  question: "¿Cual de los siguientes no es un tipo de ciclo en C++?",
  answers: [
    { text: "switch", correct: true },
    { text: "for", correct: false },
    { text: "while", correct: false },
    { text: "do-while", correct: false },
  ]
}, {
  question: "Para modificar una variable pasada como argumento a una funcion, esta se tiene que pasar:",
  answers: [
    { text: "por valor", correct: false },
    { text: "por otra funcion", correct: false},
    { text: "por referencia", correct: true },
    { text: "do-while", correct: false },
  ]
}, {
  question: "¿Cuantas veces se ejecutara el cuerpo de un ciclo while?",
  answers: [
    { text: "una o mas veces", correct: false },
    { text: "cero o mas veces", correct: true },
    { text: "ninguna", correct: false },
    { text: "diez veces", correct: false },
  ]
}, {
  question: "En un ciclo for, ¿Que parte es opcional?",
  answers: [
    { text: "inicializacion", correct: false },
    { text: "condicion", correct: false },
    { text: "actualizacion", correct: false },
    { text: "todas las anteriores", correct: true },
  ]
}, {
  question: "¿Cual de los siguientes es una declaracion valida de una funcion en C++?",
  answers: [
    { text: "function nombreFuncion()", correct: false },
    { text: "void nombreFuncion()", correct: true },
    { text: "def nombreFuncion()", correct: false },
    { text: "todas las anteriores", correct: false },
  ]
}, {
  question: "Los ciclos infinitos generalmente se consideran:",
  answers: [
    { text: "eficientes", correct: false },
    { text: "la mejor opcion", correct: false },
    { text: "un error", correct: true },
    { text: "sistemicos", correct: false },
  ]
}, {
  question: "¿Que instruccion se utiliza para salir de un ciclo prematuramente?",
  answers: [
    { text: "end", correct: false },
    { text: "continue", correct: false },
    { text: "break", correct: true },
    { text: "finalize", correct: false },
  ]
}, {
  question: "¿Que instruccion permite que la siguiente iteracion se ejecute prematuramente?",
  answers: [
    { text: "continue", correct: true },
    { text: "break", correct: false },
    { text: "go", correct: false },
    { text: "move", correct: false },
  ]
}, {
  question: "¿Cual ciclo es mejor si deseas ejecutar el bloque de codigo al menos una vez?",
  answers: [
    { text: "while", correct: false },
    { text: "do-while", correct: true },
    { text: "for", correct: false },
    { text: "ciclo infinito", correct: false },
  ]
}];

const questionElement = document.getElementById("question");
const answerButtons = document.getElementById("answer-buttons");
const nextButton = document.getElementById("next-btn");

let currentQuestionIndex = 0;
let score = 0;

function startQuiz() {
  currentQuestionIndex = 0;
  score = 0;
  nextButton.innerHTML = "Siguiente >"
  showQuestion();
}

function showQuestion() {
  resetState();
  let currentQuestion = questions[currentQuestionIndex];
  let questionNo = currentQuestion + 1;
  questionElement.innerHTML = currentQuestion.question;

  currentQuestion.answers.forEach(answer => {
    const button = document.createElement("button");
    button.innerHTML = answer.text;
    button.classList.add("answer-button");
    answerButtons.appendChild(button);
    if(answer.correct) {
      button.dataset.correct = answer.correct;
    }
    button.addEventListener("click", selectAnswer)
  });
}

function resetState() {
  nextButton.style.display = "none";
  while(answerButtons.firstChild) {
    answerButtons.removeChild(answerButtons.firstChild);
  }
}

function selectAnswer(e) {
  const selectedBtn = e.target;
  const isCorrect = selectedBtn.dataset.correct === "true";
  if(isCorrect) {
    selectedBtn.classList.add("correct");
    score++;
  } else {
    selectedBtn.classList.add("incorrect");
  }
  Array.from(answerButtons.children).forEach(button =>  {
    if(button.dataset.correct === "true") {
      button.classList.add("correct");
    }
    button.disabled = true;
  });
  nextButton.style.display = "block";
}

function showScore() {
  resetState();
  questionElement.innerHTML = `tu calificacion es ${score} / ${questions.length}.`;
  document.getElementById("back-btn").style.display = "block";
  countdownEl.style.display = "none";
}

function handleNextButton() {
  currentQuestionIndex++;
  if(currentQuestionIndex < questions.length) {
    showQuestion();
  } else {
    showScore();
  }
}

nextButton.addEventListener("click", ()=> {
  if(currentQuestionIndex < questions.length) {
    handleNextButton();
  } else {
    startQuiz();
  }
});


startQuiz();