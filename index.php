

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>Chat with the Chatbot</title>
    <script src="https://cdn.tailwindcss.com"></script>
    <style>
        .scrollable {
            overflow-y: auto;
            height: 80%;
        }
    </style>
</head>
<body class="bg-gray-200">
    <div class="bg-white mx-auto my-10 p-6 rounded-lg w-11/12 md:w-3/5 lg:w-3/5 xl:w-2/5" style="height: 70vh; width: 40vw;">
        <div class="flex justify-between items-center mb-4">
            <h2 class="text-2xl font-semibold mb-2">Together & Stronger Chatbot</h2>
            <form action="index.php" method="post" class="flex justify-end">
                <input type="hidden" name="clear_history" value="1">
                <button type="submit" class="bg-red-500 text-white p-1 rounded-lg text-xs">
                    <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-6 h-6">
                        <path stroke-linecap="round" stroke-linejoin="round" d="M14.74 9l-.346 9m-4.788 0L9.26 9m9.968-3.21c.342.052.682.107 1.022.166m-1.022-.165L18.16 19.673a2.25 2.25 0 01-2.244 2.077H8.084a2.25 2.25 0 01-2.244-2.077L4.772 5.79m14.456 0a48.108 48.108 0 00-3.478-.397m-12 .562c.34-.059.68-.114 1.022-.165m0 0a48.11 48.11 0 013.478-.397m7.5 0v-.916c0-1.18-.91-2.164-2.09-2.201a51.964 51.964 0 00-3.32 0c-1.18.037-2.09 1.022-2.09 2.201v.916m7.5 0a48.667 48.667 0 00-7.5 0" />
                    </svg>
                    </button>
            </form>
        </div>
        <hr class="mb-4">
        <div class="scrollable">
        
        <div class="mb-3 mt-20">
                <div class="bg-gray-700 p-3 rounded-lg text-white max-w-[60%]">
                <?php echo "Bonjour je suis le Bot, je suis là pour répondre à vos questions sur le déroulé des activités" ?>
                </div>
        </div>
            <?php
            session_start();

            if (isset($_POST['clear_history']) && $_POST['clear_history'] == '1') {
                session_destroy();
                session_start();
            }

            if ($_SERVER['REQUEST_METHOD'] === 'POST' && !isset($_POST['clear_history'])) {
                sleep(0.8);
                $question = $_POST['question'];
                $commande = '/Applications/MAMP/htdocs/mission1/bot_c/cmake-build-debug/bot_c ' . escapeshellarg($question);

                // création du tableau de session permettant de garder en mémoire les questions et réponses
                if (!isset($_SESSION['chat_history'])) {
                    $_SESSION['chat_history'] = [];
                }

                // permet de garder en mémoire la dernière question posée, seulement si c'était une activité sans question spécifique
                if (count($_SESSION['chat_history']) > 0) {
                    $previous_question_check = "Vous cherchez des infos sur";
                    
                    $last_chat = end($_SESSION['chat_history']);
                    $last_answer = $last_chat['answer'];
                    $last_question = $last_chat['question'];

                    if (substr($last_answer, 0, strlen($previous_question_check)) === $previous_question_check) {
                    
                        $commande = '/Applications/MAMP/htdocs/mission1/bot_c/cmake-build-debug/bot_c ' . escapeshellarg($last_question . ' ' . $question);
                    }
                } 

                $output = shell_exec($commande);
                

                array_push($_SESSION['chat_history'], ['question' => $question, 'answer' => $output]);
            }
            
            if (isset($_SESSION['chat_history'])) {
                foreach ($_SESSION['chat_history'] as $chat) {
            ?>
            <div class="mb-3">
                <div class="bg-blue-500 p-3 rounded-lg text-white float-right max-w-[40%] text-right">
                    <?php echo htmlspecialchars($chat['question']); ?>
                </div>
                <div class="clearfix"></div>
            </div>
            <div class="mb-3 mt-20">
                <div class="bg-gray-700 p-3 rounded-lg text-white max-w-[60%]">
                    <?php echo htmlspecialchars($chat['answer']); ?>
                </div>
            </div>
            <?php
                }
            }
            ?>
        </div>
        <form action="index.php" method="post" class="mt-4">
            <div class="flex flex-row">
                <input type="text" id="question" name="question" required class="border border-gray-300 p-2 w-full rounded-lg">
                <button type="submit" class="bg-blue-500 text-white px-2 py-2 rounded-lg float-right flex flex-row justify-between">
                    <p class="mr-2">Envoyer</p>
                    <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-6 h-6 ">
                        <path stroke-linecap="round" stroke-linejoin="round" d="M15 11.25l-3-3m0 0l-3 3m3-3v7.5M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
                    </svg>
                </button>
            </div>
                <div class="clearfix"></div>
        </form>
    </div>

    <!-- code qui permet de scroller automatiquement vers le bas de la conversation -->
    <script>
        const scrollable = document.querySelector(".scrollable");
        scrollable.scrollTop = scrollable.scrollHeight;
    </script>
<?php
//  print('$_SESSION=<pre>'.print_r($_SESSION, true).'</pre><br><br>');

?>
</body>
</html>
