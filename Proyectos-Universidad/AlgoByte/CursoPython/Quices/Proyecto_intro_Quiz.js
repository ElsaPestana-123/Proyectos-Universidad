function submitQuiz() {
    // Respuestas correctas
    var correctAnswers = {
        q1: "true",
        q2: "true",
        q3: "false",
        q4: "true",
        q5: "false",
        q6: "true",
        q7: "true",
        q8: "true",
        q9: "true",
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
}
