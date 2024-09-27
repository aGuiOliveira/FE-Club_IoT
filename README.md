# FE-Club_IoT

## Introdução

A Internet das Coisas (IoT) refere-se à interconexão de dispositivos físicos, como eletrodomésticos, veículos e sensores, através da internet. Esses dispositivos coletam e compartilham dados, permitindo automação e controle remoto.

#### Conceitos Básicos:
**Sensores e Atuadores:** Dispositivos que coletam dados do ambiente e executam ações.
**Conectividade:** Uso de redes (Wi-Fi, Bluetooth, etc.) para comunicação entre dispositivos.
**Plataformas de Nuvem:** Armazenamento e processamento de dados coletados.
**Análise de Dados:** Extração de insights a partir dos dados para tomada de decisões.
#### Importância da IoT:
**Eficiência Operacional:** Automação de processos e otimização de recursos.
**Tomada de Decisões Informadas:** Dados em tempo real ajudam na identificação de padrões e anomalias.
**Qualidade de Vida:** Aplicações em saúde, segurança e conforto doméstico.

## Descrição do projeto
O projeto FE-Club_IoT tem como objetivo principal utilizar sensores avançados para calcular o desgaste dos pneus de um carro de Fórmula E.

### Como Funciona?
Atualmente, as equipes de Fórmula E determinam o desgaste dos pneus com base na velocidade do carro e na temperatura do solo em contato com os pneus. Nosso projeto aprimora essa metodologia utilizando dois tipos de sensores:

Sensor de Movimento: Este sensor identifica quando o carro completa uma volta na pista, permitindo calcular a velocidade média do veículo.
Sensor de Temperatura: Este sensor mede a temperatura da pista, fornecendo dados cruciais sobre as condições do solo.
Combinando as informações desses sensores, podemos calcular o delta de desgaste dos pneus com maior precisão. Isso nos permite prever o momento ideal para chamar o piloto ao box para a troca dos pneus, otimizando o desempenho e a segurança durante a corrida.

**Componentes utilizados no projeto:**

1 ESP23

1 Sensor de temperatura DS18B20

1 Sensor de movimento PIR

## Arquitetura
Para tornar o projeto possivel e funcional, foi criado uma maquina virtual linux na Azure, onde foi instalado o [Fiware Descomplicado](https://github.com/fabiocabrini/fiware/tree/main) do professor Fábio Cabrini.

O FIWARE Descomplicado é uma ferramenta que torna simples o processo de configurar os principais GEs (Generic Enablers) oferecidos pela FIWARE Foundation. Desenvolvido como uma solução leve baseada no Docker, este recurso foi projetado para ser flexível, adaptando-se facilmente a várias plataformas computacionais, sistemas operacionais e provedores de serviços em nuvem (CSP, do inglês Cloud Service Provider).

![image](https://github.com/user-attachments/assets/85222c1b-1272-4cd7-88d3-5caaef20cfeb)

## Desenvolvimento

Para executar o projeto, será necessário realizar os seguintes passos:

### Criação de uma VM na Azure

1 - Crie uma conta na Azure

2 - Crie uma VM. A própria Azure oferece um pequeno curso gratuito sobre os serviços que eles oferecem. [Assista como criar uma VM.](https://portal.azure.com/#view/Microsoft_Azure_Resources/QuickstartTutorialBlade/checklistId/get-started-with-azure/sectionId/get-started-deploy-resource/lessonId/get-started-deploy-azure-virtual-machines)  

3 - Depois de criar a VM será necessário acessar as configurações de rede para permitir o acesso através das portas 4041,8666,1026 e 1883 (portas utilizadas para a conexão com o broker)

### Instalação do Docker
Para instalar o Docker, siga o tutorial oficial da Digital Ocean: [Como instalar e utilizar o Docker no Ubunto](https://www.digitalocean.com/community/tutorials/how-to-install-and-use-docker-on-ubuntu-20-04-pt)

### Instalação do Fiware Descomplicado
Para instalar o Fiware siga os comandos no terminal da VM:

1 - Copiar os arquivos do repositório de Fiware Descomplicado

_git clone https://github.com/fabiocabrini/fiware_

2 - Entrar na pasta do Fiware

_cd fiware_

3 - Rodar os containers

_sudo docker compose up -d_

4 - Verificar status dos containers

_sudo docker stats_

### Verificação dos serviços através do Health Check
Após a correta inicialização dos containers Docker com a estrutura do Fiware, realizar um teste 
de “Health Check” dos componentes “IOT Agent MQTT”, “Orion Context Broker” e do “STH –
Comet” utilizando o software Postman utilizando a collection.json disponibilizada no GitHub do 
[Fiware descomplicado](https://github.com/fabiocabrini/fiware/blob/main/FIWARE%20Descomplicado.postman_collec
tion.json) disponibilizado pelo prof. Fabio Cabrini.

IMPORTANTE: Para conseguir realizar o Health Check, será necessário usar o IP público da sua máquina, você pode encontrar essa informação na parte inicial da VM na Azure como no print abaixo. Para conseguir conectar você precisa ter seguido corretamente o passo 3 da criação da VM na Azure.

![image](https://github.com/user-attachments/assets/0ffd5d3b-5ffd-463b-a091-3cfac11a6d83)

### Configuração dos componentes no Wokwi
Para fazer o teste do projeto de forma virtual, você pode utilizar a plataforma Wokwi para montar o prototipo e utilizar o código do arquivo desse projeto para rodar. 
Ou se preferir, você pode acessar o projeto do Wokwi pronto nesse link: [Wokwi - FE-Club_IoT](https://wokwi.com/projects/410139043658299393)

.

.

.

.

.

.

.

Esse projeto foi desenvolvido para a entrega da Sprint 3 do Challenge - 2024 1ES da FIAP.
- Guilherme Oliveira Santana de Almeida 555180
- Vinicius Monteiro Araujo 555088
- Rafael Duarte de Freitas 558644
- Rafael Gaspar Bragança Martins 557228
