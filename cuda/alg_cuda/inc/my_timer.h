#ifndef TIMER_H
#define TIMER_H

/**
 *@brief  Init timer
 *@param  None
 *@retval None
 */
void initTimer(void);

/**
 *@brief  Start timer
 *@param  None
 *@retval None
 */
void startTimer(void);

/**
 *@brief  Stop timer
 *@param  None
 *@retval None
 */
void stopTimer(void);

/**
 *@brief  Get timer
 *@param  None
 *@retval timer value in ms
 */
float getTimer(void);

/**
 *@brief  Delete timer
 *@param  None
 *@retval None
 */
void deleteTimer(void);

#endif // TIMER_H
