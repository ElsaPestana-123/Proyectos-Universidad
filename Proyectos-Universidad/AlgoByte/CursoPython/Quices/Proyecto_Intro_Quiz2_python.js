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
  question: "¿Qué palabra clave se utiliza para crear un bucle que se ejecuta mientras una condición sea verdadera?",
  answers: [
    { text: "for", correct: false },
    { text: "while", correct: true },
    { text: "loop", correct: false },
    { text: "repeat", correct: false },
  ]
}, {
  question: "¿Cuál de los siguientes bucles es adecuado para iterar sobre una lista de elementos?:",
  answers: [
    { text: "foreach", correct: false },
    { text: "for", correct: true},
    { text: "while", correct: false },
    { text: "loop", correct: false },
  ]
}, {
  question: "¿Qué palabra clave se usa para salir de un bucle inmediatamente, independientemente de la condición?",
  answers: [
    { text: "exit", correct: false },
    { text: "stop", correct: false },
    { text: "break", correct: true },
    { text: "quit", correct: false },
  ]
}, {
  question: "¿Qué palabra clave se usa para omitir la ejecución del código restante en una iteración y pasar a la siguiente iteración en un bucle?",
  answers: [
    { text: "continue", correct: true },
    { text: "next", correct: false },
    { text: "pass", correct: false },
    { text: "skip", correct: false },
  ]
}, {
  question: "En un bucle for, si se usa la función range(5), ¿cuántas veces se ejecutará el bucle?",
  answers: [
    { text: "4", correct: false },
    { text: "0", correct: false },
    { text: "6", correct: false },
    { text: "5", correct: true },
  ]
}, {
  question: "¿Cómo se llama a una función en Python?",
  answers: [
    { text: "function_name()", correct: true },
    { text: "call function_name", correct: false },
    { text: "execute function_name", correct: false },
    { text: "function_name;", correct: false },
  ]
}, {
  question: "¿Qué palabra clave se utiliza para definir una función en Python?",
  answers: [
    { text: "function", correct: false },
    { text: "define", correct: false },
    { text: "def", correct: true },
    { text: "func", correct: false },
  ]
}, {
  question: "¿Qué palabra clave se usa para devolver un valor desde una función en Python?",
  answers: [
    { text: "return", correct: true },
    { text: "output", correct: false },
    { text: "yield", correct: false },
    { text: "give", correct: false },
  ]
}, {
  question: "¿Qué ocurre si una función no tiene una sentencia return en Python?",
  answers: [
    { text: "Retorna un valor nulo.", correct: false },
    { text: "Retorna None", correct: true },
    { text: "Retorna una cadena vacía.", correct: false },
    { text: "Dará un error.", correct: false },
  ]
}, {
 question: "¿Cómo se llama a un parámetro que tiene un valor por defecto en una función?",
  answers: [
    { text: "Parámetro obligatorio", correct: false },
    { text: "Parámetro opcional", correct: false },
    { text: "Parámetro fijo", correct: false },
    { text: "Parámetro predeterminado", correct: true },
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