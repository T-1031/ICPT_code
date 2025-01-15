% MATLAB代码：生成矩形波并提取基波
clc;
clear;
close all;

% 设置参数
U_DC = 1; % 输入直流信号幅值
phi = 2.5; % 导通角，取值范围为 (0, 2.93)
fHRTIM = 144000; % HRTIM 时钟频率 (kHz)
fHRCK = fHRTIM * 8;
Period = 10472;
fPWM = fHRCK / Period; % PWM 频率 (kHz)
T = 1 / fPWM; % PWM 周期
fDTG = fHRTIM * 8;
T_dead = 180 / fDTG; % 死区时间 (ms)
TD = T_dead / T * 2 * pi; % 死区时间 (0, 2*pi)
DT = pi - 2 * TD - phi; % (0, 0.93)
% DT = 0;
% phi = pi - 2 * TD - DT;

CMP1 = round(T_dead / T * Period); 
CMP2 = round((pi - DT) / (2 * pi) * Period);
CMP3 = round(Period / 2);
CMP4 = round((2 * pi - TD - DT) / (2 * pi) * Period);
fprintf('Period: %d\n', Period);
fprintf('CMP1: %d\n', CMP1);
fprintf('CMP2: %d\n', CMP2);
fprintf('CMP3: %d\n', CMP3);
fprintf('CMP4: %d\n', CMP4);

% 基本参数
Fs = 1000; % 采样率 (Hz)
Ts = 1 / Fs; % 采样周期
L = 1000; % 信号长度
t = (0:L-1) * Ts *2 * pi; % (0, 2pi)

% 滤波前输出信号
u_AB = U_DC * ((mod(t, 2*pi) > CMP1/Period*2*pi) & (mod(t, 2*pi) < CMP2/Period*2*pi-TD)) - ... % 正半周期
       U_DC * ((mod(t, 2*pi) > CMP1/Period*2*pi+pi) & (mod(t, 2*pi) < CMP2/Period*2*pi-TD+pi));    % 负半周期

figure;
plot(t, u_AB, 'b', 'LineWidth', 1.5);
title('滤波前');
xlabel('\omega t');
ylabel('幅值');
grid on;
xlim([0, 4*pi]);

% 傅里叶变换
Y = fft(u_AB);            % 快速傅里叶变换
P2 = abs(Y / L);          % 双边幅值谱
P1 = P2(1:L/2+1);         % 单边幅值谱
P1(2:end-1) = 2*P1(2:end-1); % 单边幅值谱振幅调整

% 提取频率分量
frequencies = Fs * (0:(L/2)) / L; % 频率向量
[~, idx] = max(P1(2:end));        % 找到基波
idx = idx + 1;
base_frequency = frequencies(idx); % 基波频率
base_amplitude = P1(idx);          % 基波幅值

% 提取基波信号
base_waveform = base_amplitude * sin(base_frequency * t);

% 绘制基波信号
figure;
plot(t, base_waveform, 'r', 'LineWidth', 1.5);
title('滤波后');
xlabel('\omega t');
ylabel('幅值');
grid on;
xlim([0, 4*pi]);

% 打印信息
fprintf('PWM 频率：%.3f kHz\n', fPWM);
fprintf('输入幅值：%.2f\n', U_DC);
fprintf('导通角：%.2f (rad)\n',phi);
fprintf('输出幅值：%.3f\n', base_amplitude);
fprintf('输出有效值：%.3f\n', base_amplitude/sqrt(2));